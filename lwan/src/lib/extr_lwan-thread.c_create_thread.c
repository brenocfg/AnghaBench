#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lwan_thread {int* pipe_fd; int /*<<< orphan*/  pending_fds; struct lwan* lwan; int /*<<< orphan*/  self; int /*<<< orphan*/  epoll_fd; int /*<<< orphan*/  wheel; } ;
struct TYPE_4__ {size_t max_fd; } ;
struct lwan {TYPE_2__ thread; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ptr; } ;
struct epoll_event {TYPE_1__ data; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int EFD_CLOEXEC ; 
 int EFD_NONBLOCK ; 
 int EFD_SEMAPHORE ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CLOEXEC ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 int /*<<< orphan*/  PTHREAD_SCOPE_SYSTEM ; 
 int /*<<< orphan*/  epoll_create1 (int /*<<< orphan*/ ) ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int eventfd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lwan_status_critical (char*,...) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 
 int /*<<< orphan*/  memset (struct lwan_thread*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pipe2 (int*,int) ; 
 scalar_t__ pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_attr_setscope (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lwan_thread*) ; 
 scalar_t__ spsc_queue_init (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  thread_io_loop ; 
 int /*<<< orphan*/  timeouts_open (int*) ; 

__attribute__((used)) static void create_thread(struct lwan *l, struct lwan_thread *thread)
{
    int ignore;
    pthread_attr_t attr;

    memset(thread, 0, sizeof(*thread));
    thread->lwan = l;

    thread->wheel = timeouts_open(&ignore);
    if (!thread->wheel)
        lwan_status_critical("Could not create timer wheel");

    if ((thread->epoll_fd = epoll_create1(EPOLL_CLOEXEC)) < 0)
        lwan_status_critical_perror("epoll_create");

    if (pthread_attr_init(&attr))
        lwan_status_critical_perror("pthread_attr_init");

    if (pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM))
        lwan_status_critical_perror("pthread_attr_setscope");

    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE))
        lwan_status_critical_perror("pthread_attr_setdetachstate");

#if defined(HAVE_EVENTFD)
    int efd = eventfd(0, EFD_NONBLOCK | EFD_SEMAPHORE | EFD_CLOEXEC);
    if (efd < 0)
        lwan_status_critical_perror("eventfd");

    thread->pipe_fd[0] = thread->pipe_fd[1] = efd;
#else
    if (pipe2(thread->pipe_fd, O_NONBLOCK | O_CLOEXEC) < 0)
        lwan_status_critical_perror("pipe");
#endif

    struct epoll_event event = { .events = EPOLLIN, .data.ptr = NULL };
    if (epoll_ctl(thread->epoll_fd, EPOLL_CTL_ADD, thread->pipe_fd[0], &event) < 0)
        lwan_status_critical_perror("epoll_ctl");

    if (pthread_create(&thread->self, &attr, thread_io_loop, thread))
        lwan_status_critical_perror("pthread_create");

    if (pthread_attr_destroy(&attr))
        lwan_status_critical_perror("pthread_attr_destroy");

    size_t n_queue_fds = thread->lwan->thread.max_fd;
    if (spsc_queue_init(&thread->pending_fds, n_queue_fds) < 0) {
        lwan_status_critical("Could not initialize pending fd "
                             "queue width %zu elements", n_queue_fds);
    }
}
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
struct timeout_queue {int dummy; } ;
struct lwan_thread {int epoll_fd; int* pipe_fd; struct lwan* lwan; } ;
struct lwan_connection {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  barrier; struct lwan_thread* threads; scalar_t__ max_fd; } ;
struct lwan {TYPE_2__ thread; int /*<<< orphan*/  conns; } ;
struct TYPE_3__ {struct lwan_connection* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
struct coro_switcher {int dummy; } ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ EINVAL ; 
 int EPOLLHUP ; 
 int EPOLLRDHUP ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  accept_nudge (int const,struct lwan_thread*,int /*<<< orphan*/ ,struct timeout_queue*,struct coro_switcher*,int) ; 
 struct epoll_event* calloc (size_t,int) ; 
 int epoll_wait (int,struct epoll_event*,int const,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct epoll_event*) ; 
 int /*<<< orphan*/  lwan_set_thread_name (char*) ; 
 int /*<<< orphan*/  lwan_status_critical (char*) ; 
 int /*<<< orphan*/  lwan_status_debug (char*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resume_coro (struct timeout_queue*,struct lwan_connection*,int) ; 
 int /*<<< orphan*/  timeout_queue_init (struct timeout_queue*,struct lwan*) ; 
 int /*<<< orphan*/  timeout_queue_kill (struct timeout_queue*,struct lwan_connection*) ; 
 int /*<<< orphan*/  timeout_queue_kill_all (struct timeout_queue*) ; 
 int /*<<< orphan*/  timeout_queue_move_to_last (struct timeout_queue*,struct lwan_connection*) ; 
 int turn_timer_wheel (struct timeout_queue*,struct lwan_thread*,int) ; 
 int /*<<< orphan*/  update_date_cache (struct lwan_thread*) ; 

__attribute__((used)) static void *thread_io_loop(void *data)
{
    struct lwan_thread *t = data;
    int epoll_fd = t->epoll_fd;
    const int read_pipe_fd = t->pipe_fd[0];
    const int max_events = min((int)t->lwan->thread.max_fd, 1024);
    struct lwan *lwan = t->lwan;
    struct epoll_event *events;
    struct coro_switcher switcher;
    struct timeout_queue tq;

    lwan_status_debug("Worker thread #%zd starting",
                      t - t->lwan->thread.threads + 1);
    lwan_set_thread_name("worker");

    events = calloc((size_t)max_events, sizeof(*events));
    if (UNLIKELY(!events))
        lwan_status_critical("Could not allocate memory for events");

    update_date_cache(t);

    timeout_queue_init(&tq, lwan);

    pthread_barrier_wait(&lwan->thread.barrier);

    for (;;) {
        int timeout = turn_timer_wheel(&tq, t, epoll_fd);
        int n_fds = epoll_wait(epoll_fd, events, max_events, timeout);

        if (UNLIKELY(n_fds < 0)) {
            if (errno == EBADF || errno == EINVAL)
                break;
            continue;
        }

        for (struct epoll_event *event = events; n_fds--; event++) {
            struct lwan_connection *conn;

            if (UNLIKELY(!event->data.ptr)) {
                accept_nudge(read_pipe_fd, t, lwan->conns, &tq, &switcher,
                             epoll_fd);
                continue;
            }

            conn = event->data.ptr;

            if (UNLIKELY(event->events & (EPOLLRDHUP | EPOLLHUP))) {
                timeout_queue_kill(&tq, conn);
                continue;
            }

            resume_coro(&tq, conn, epoll_fd);
            timeout_queue_move_to_last(&tq, conn);
        }
    }

    pthread_barrier_wait(&lwan->thread.barrier);

    timeout_queue_kill_all(&tq);
    free(events);

    return NULL;
}
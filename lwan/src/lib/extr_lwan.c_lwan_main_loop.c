#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lwan_fd_watch {int dummy; } ;
struct lwan {int main_socket; int /*<<< orphan*/  epfd; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;
struct epoll_event {scalar_t__ events; TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLRDHUP ; 
 int /*<<< orphan*/  N_ELEMENTS (struct epoll_event*) ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ SIG_ERR ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  accept_connection_coro ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  coro_resume_value (int /*<<< orphan*/ ,int) ; 
 int epoll_wait (int /*<<< orphan*/ ,struct epoll_event*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  lwan_status_critical (char*) ; 
 int /*<<< orphan*/  lwan_status_info (char*) ; 
 int /*<<< orphan*/  lwan_status_perror (char*) ; 
 int /*<<< orphan*/  lwan_unwatch_fd (struct lwan*,struct lwan_fd_watch*) ; 
 struct lwan_fd_watch* lwan_watch_fd (struct lwan*,int,int,int /*<<< orphan*/ ,struct lwan*) ; 
 int main_socket ; 
 int /*<<< orphan*/  sigint_handler ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lwan_main_loop(struct lwan *l)
{
    struct epoll_event evs[16];
    struct lwan_fd_watch *watch;

    assert(main_socket == -1);
    main_socket = l->main_socket;

    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        lwan_status_critical("Could not set signal handler");

    watch = lwan_watch_fd(l, l->main_socket, EPOLLIN | EPOLLHUP | EPOLLRDHUP,
                          accept_connection_coro, l);
    if (!watch)
        lwan_status_critical("Could not watch main socket");

    lwan_status_info("Ready to serve");

    while (true) {
        int n_evs = epoll_wait(l->epfd, evs, N_ELEMENTS(evs), -1);

        if (UNLIKELY(n_evs < 0)) {
            if (main_socket < 0)
                break;
            if (errno == EINTR || errno == EAGAIN)
                continue;
            lwan_status_perror("epoll_wait");
            break;
        }

        for (int i = 0; i < n_evs; i++) {
            if (!coro_resume_value(evs[i].data.ptr, (int)evs[i].events))
                break;
        }
    }

    lwan_unwatch_fd(l, watch);
}
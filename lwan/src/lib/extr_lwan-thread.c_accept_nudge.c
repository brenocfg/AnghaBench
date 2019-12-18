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
typedef  int /*<<< orphan*/  uint64_t ;
struct timeout_queue {int /*<<< orphan*/  timeout; } ;
struct lwan_thread {int /*<<< orphan*/  wheel; int /*<<< orphan*/  pending_fds; } ;
struct lwan_connection {int dummy; } ;
struct TYPE_2__ {struct lwan_connection* ptr; } ;
struct epoll_event {int /*<<< orphan*/  events; TYPE_1__ data; } ;
struct coro_switcher {int dummy; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_EVENTS_READ ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 scalar_t__ LIKELY (int) ; 
 int /*<<< orphan*/  conn_flags_to_epoll_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spawn_coro (struct lwan_connection*,struct coro_switcher*,struct timeout_queue*) ; 
 scalar_t__ spsc_queue_pop (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  timeouts_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void accept_nudge(int pipe_fd,
                         struct lwan_thread *t,
                         struct lwan_connection *conns,
                         struct timeout_queue *tq,
                         struct coro_switcher *switcher,
                         int epoll_fd)
{
    uint64_t event;
    int new_fd;

    /* Errors are ignored here as pipe_fd serves just as a way to wake the
     * thread from epoll_wait().  It's fine to consume the queue at this
     * point, regardless of the error type. */
    (void)read(pipe_fd, &event, sizeof(event));

    while (spsc_queue_pop(&t->pending_fds, &new_fd)) {
        struct lwan_connection *conn = &conns[new_fd];
        struct epoll_event ev = {
            .data.ptr = conn,
            .events = conn_flags_to_epoll_events(CONN_EVENTS_READ),
        };

        if (LIKELY(!epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &ev)))
            spawn_coro(conn, switcher, tq);
    }

    timeouts_add(t->wheel, &tq->timeout, 1000);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lwan_fd_watch {scalar_t__ fd; int /*<<< orphan*/  coro; } ;
struct lwan {scalar_t__ main_socket; int /*<<< orphan*/  epfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  coro_free (int /*<<< orphan*/ ) ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct lwan_fd_watch*) ; 
 int /*<<< orphan*/  lwan_status_perror (char*,scalar_t__) ; 

void lwan_unwatch_fd(struct lwan *l, struct lwan_fd_watch *w)
{
    if (l->main_socket != w->fd) {
        if (epoll_ctl(l->epfd, EPOLL_CTL_DEL, w->fd, NULL) < 0)
            lwan_status_perror("Could not unwatch fd %d", w->fd);
    }

    coro_free(w->coro);
    free(w);
}
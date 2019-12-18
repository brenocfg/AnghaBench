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
typedef  int /*<<< orphan*/  uint32_t ;
struct lwan_fd_watch {int fd; int /*<<< orphan*/  coro; } ;
struct lwan {int /*<<< orphan*/  epfd; int /*<<< orphan*/  switcher; } ;
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;
struct epoll_event {TYPE_1__ data; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  coro_function_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  coro_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coro_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  free (struct lwan_fd_watch*) ; 
 struct lwan_fd_watch* malloc (int) ; 

struct lwan_fd_watch *lwan_watch_fd(struct lwan *l,
                                    int fd,
                                    uint32_t events,
                                    coro_function_t coro_fn,
                                    void *data)
{
    struct lwan_fd_watch *watch;

    watch = malloc(sizeof(*watch));
    if (!watch)
        return NULL;

    watch->coro = coro_new(&l->switcher, coro_fn, data);
    if (!watch->coro)
        goto out;

    struct epoll_event ev = {.events = events, .data.ptr = watch->coro};
    if (epoll_ctl(l->epfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        coro_free(watch->coro);
        goto out;
    }

    watch->fd = fd;
    return watch;

out:
    free(watch);
    return NULL;
}
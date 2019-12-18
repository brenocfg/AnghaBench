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
struct lwan {scalar_t__ epfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CLOEXEC ; 
 scalar_t__ epoll_create1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 

__attribute__((used)) static void lwan_fd_watch_init(struct lwan *l)
{
    l->epfd = epoll_create1(EPOLL_CLOEXEC);
    if (l->epfd < 0)
        lwan_status_critical_perror("epoll_create1");
}
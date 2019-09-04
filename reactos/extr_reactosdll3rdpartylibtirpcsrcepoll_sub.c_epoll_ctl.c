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
struct epoll_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_epoll_ctl ; 
 int syscall (int /*<<< orphan*/ ,int,int,int,struct epoll_event*) ; 

int
epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
{

	return (syscall(__NR_epoll_ctl, epfd, op, fd, event));
}
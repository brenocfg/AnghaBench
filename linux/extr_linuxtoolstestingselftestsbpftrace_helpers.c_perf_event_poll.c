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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int poll (struct pollfd*,int,int) ; 

__attribute__((used)) static int perf_event_poll(int fd)
{
	struct pollfd pfd = { .fd = fd, .events = POLLIN };

	return poll(&pfd, 1, 1000);
}
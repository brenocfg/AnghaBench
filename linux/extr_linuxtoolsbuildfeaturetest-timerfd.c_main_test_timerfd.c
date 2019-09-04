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
struct itimerspec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  TFD_NONBLOCK ; 
 int timerfd_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ timerfd_settime (int,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

int main(void)
{
	struct itimerspec new_value;

	int fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
	if (fd < 0)
		return 1;

	if (timerfd_settime(fd, 0, &new_value, NULL) != 0)
		return 1;

	return 0;
}
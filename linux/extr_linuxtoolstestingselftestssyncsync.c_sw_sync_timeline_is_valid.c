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

/* Variables and functions */
 int /*<<< orphan*/  F_GETFD ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sw_sync_timeline_is_valid(int fd)
{
	int status;

	if (fd == -1)
		return 0;

	status = fcntl(fd, F_GETFD, 0);
	return (status >= 0);
}
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
typedef  unsigned int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SW_SYNC_IOC_INC ; 
 int ioctl (int,int /*<<< orphan*/ ,unsigned int*) ; 

int sw_sync_timeline_inc(int fd, unsigned int count)
{
	__u32 arg = count;

	return ioctl(fd, SW_SYNC_IOC_INC, &arg);
}
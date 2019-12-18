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
struct file {int dummy; } ;

/* Variables and functions */
 long rtc_do_ioctl (unsigned int,unsigned long) ; 

__attribute__((used)) static long rtc_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;
	ret = rtc_do_ioctl(cmd, arg);
	return ret;
}
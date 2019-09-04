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
struct syscall_arg {unsigned long val; } ;

/* Variables and functions */
 size_t ioctl__scnprintf_cmd (unsigned long,char*,size_t) ; 

size_t syscall_arg__scnprintf_ioctl_cmd(char *bf, size_t size, struct syscall_arg *arg)
{
	unsigned long cmd = arg->val;

	return ioctl__scnprintf_cmd(cmd, bf, size);
}
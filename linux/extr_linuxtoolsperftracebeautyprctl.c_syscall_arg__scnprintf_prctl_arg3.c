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
struct syscall_arg {int dummy; } ;

/* Variables and functions */
 int PR_SET_MM ; 
 size_t syscall_arg__scnprintf_hex (char*,size_t,struct syscall_arg*) ; 
 size_t syscall_arg__scnprintf_long (char*,size_t,struct syscall_arg*) ; 
 int syscall_arg__val (struct syscall_arg*,int /*<<< orphan*/ ) ; 

size_t syscall_arg__scnprintf_prctl_arg3(char *bf, size_t size, struct syscall_arg *arg)
{
	int option = syscall_arg__val(arg, 0);

	if (option == PR_SET_MM)
		return syscall_arg__scnprintf_hex(bf, size, arg);

	return syscall_arg__scnprintf_long(bf, size, arg);
}
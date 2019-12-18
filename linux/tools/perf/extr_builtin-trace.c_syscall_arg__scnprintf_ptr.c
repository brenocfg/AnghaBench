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
struct syscall_arg {scalar_t__ val; } ;

/* Variables and functions */
 size_t scnprintf (char*,size_t,char*) ; 
 size_t syscall_arg__scnprintf_hex (char*,size_t,struct syscall_arg*) ; 

size_t syscall_arg__scnprintf_ptr(char *bf, size_t size, struct syscall_arg *arg)
{
	if (arg->val == 0)
		return scnprintf(bf, size, "NULL");
	return syscall_arg__scnprintf_hex(bf, size, arg);
}
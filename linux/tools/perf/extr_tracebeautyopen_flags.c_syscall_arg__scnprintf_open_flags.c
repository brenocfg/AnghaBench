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
struct syscall_arg {int val; int mask; int idx; int /*<<< orphan*/  show_string_prefix; } ;

/* Variables and functions */
 int O_CREAT ; 
 size_t open__scnprintf_flags (int,char*,size_t,int /*<<< orphan*/ ) ; 

size_t syscall_arg__scnprintf_open_flags(char *bf, size_t size, struct syscall_arg *arg)
{
	int flags = arg->val;

	if (!(flags & O_CREAT))
		arg->mask |= 1 << (arg->idx + 1); /* Mask the mode parm */

	return open__scnprintf_flags(flags, bf, size, arg->show_string_prefix);
}
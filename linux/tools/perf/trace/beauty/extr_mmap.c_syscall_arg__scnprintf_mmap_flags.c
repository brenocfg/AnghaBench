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
struct syscall_arg {unsigned long val; int mask; int /*<<< orphan*/  show_string_prefix; } ;

/* Variables and functions */
 unsigned long MAP_ANONYMOUS ; 
 size_t mmap__scnprintf_flags (unsigned long,char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_mmap_flags(char *bf, size_t size,
						struct syscall_arg *arg)
{
	unsigned long flags = arg->val;

	if (flags & MAP_ANONYMOUS)
		arg->mask |= (1 << 4) | (1 << 5); /* Mask 4th ('fd') and 5th ('offset') args, ignored */

	return mmap__scnprintf_flags(flags, bf, size, arg->show_string_prefix);
}
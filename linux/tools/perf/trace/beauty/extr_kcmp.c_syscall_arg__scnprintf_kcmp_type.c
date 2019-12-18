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
 unsigned long KCMP_FILE ; 
 size_t kcmp__scnprintf_type (unsigned long,char*,size_t,int /*<<< orphan*/ ) ; 

size_t syscall_arg__scnprintf_kcmp_type(char *bf, size_t size, struct syscall_arg *arg)
{
	unsigned long type = arg->val;

	if (type != KCMP_FILE)
		arg->mask |= (1 << 3) | (1 << 4); /* Ignore idx1 and idx2 */

	return kcmp__scnprintf_type(type, bf, size, arg->show_string_prefix);
}
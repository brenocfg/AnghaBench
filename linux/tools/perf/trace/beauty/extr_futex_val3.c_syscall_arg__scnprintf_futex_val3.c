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
struct syscall_arg {unsigned int val; scalar_t__ show_string_prefix; } ;

/* Variables and functions */
 unsigned int FUTEX_BITSET_MATCH_ANY ; 
 size_t scnprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t syscall_arg__scnprintf_futex_val3(char *bf, size_t size, struct syscall_arg *arg)
{
	const char *prefix = "FUTEX_BITSET_";
	unsigned int bitset = arg->val;

	if (bitset == FUTEX_BITSET_MATCH_ANY)
		return scnprintf(bf, size, "%s%s", arg->show_string_prefix ? prefix : "", "MATCH_ANY");

	return scnprintf(bf, size, "%#xd", bitset);
}
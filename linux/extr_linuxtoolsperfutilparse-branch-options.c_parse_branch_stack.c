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
struct option {scalar_t__ value; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int parse_branch_str (char const*,scalar_t__*) ; 

int
parse_branch_stack(const struct option *opt, const char *str, int unset)
{
	__u64 *mode = (__u64 *)opt->value;

	if (unset)
		return 0;

	/*
	 * cannot set it twice, -b + --branch-filter for instance
	 */
	if (*mode)
		return -1;

	return parse_branch_str(str, mode);
}
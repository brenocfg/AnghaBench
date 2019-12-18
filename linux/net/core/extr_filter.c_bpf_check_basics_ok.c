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
struct sock_filter {int dummy; } ;

/* Variables and functions */
 unsigned int BPF_MAXINSNS ; 

__attribute__((used)) static bool bpf_check_basics_ok(const struct sock_filter *filter,
				unsigned int flen)
{
	if (filter == NULL)
		return false;
	if (flen == 0 || flen > BPF_MAXINSNS)
		return false;

	return true;
}
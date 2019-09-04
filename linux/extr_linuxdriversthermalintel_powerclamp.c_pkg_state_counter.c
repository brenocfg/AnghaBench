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
typedef  scalar_t__ u64 ;
struct pkg_cstate_info {int skip; scalar_t__ msr_index; } ;

/* Variables and functions */
 struct pkg_cstate_info* pkg_cstates ; 
 int /*<<< orphan*/  rdmsrl_safe (scalar_t__,scalar_t__*) ; 

__attribute__((used)) static u64 pkg_state_counter(void)
{
	u64 val;
	u64 count = 0;
	struct pkg_cstate_info *info = pkg_cstates;

	while (info->msr_index) {
		if (!info->skip) {
			if (!rdmsrl_safe(info->msr_index, &val))
				count += val;
			else
				info->skip = true;
		}
		info++;
	}

	return count;
}
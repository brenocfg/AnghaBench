#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int* d; } ;
struct snd_ctl_elem_info {unsigned int count; TYPE_1__ dimen; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 

__attribute__((used)) static bool validate_element_member_dimension(struct snd_ctl_elem_info *info)
{
	unsigned int members;
	unsigned int i;

	if (info->dimen.d[0] == 0)
		return true;

	members = 1;
	for (i = 0; i < ARRAY_SIZE(info->dimen.d); ++i) {
		if (info->dimen.d[i] == 0)
			break;
		members *= info->dimen.d[i];

		/*
		 * info->count should be validated in advance, to guarantee
		 * calculation soundness.
		 */
		if (members > info->count)
			return false;
	}

	for (++i; i < ARRAY_SIZE(info->dimen.d); ++i) {
		if (info->dimen.d[i] > 0)
			return false;
	}

	return members == info->count;
}
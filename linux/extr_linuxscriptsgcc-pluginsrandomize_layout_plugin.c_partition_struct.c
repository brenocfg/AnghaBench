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
typedef  scalar_t__ tree ;
struct partition_group {scalar_t__ tree_start; unsigned long start; unsigned long length; } ;

/* Variables and functions */
 unsigned long INT_MAX ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ int_size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct partition_group*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void partition_struct(tree *fields, unsigned long length, struct partition_group *size_groups, unsigned long *num_groups)
{
	unsigned long i;
	unsigned long accum_size = 0;
	unsigned long accum_length = 0;
	unsigned long group_idx = 0;

	gcc_assert(length < INT_MAX);

	memset(size_groups, 0, sizeof(struct partition_group) * length);

	for (i = 0; i < length; i++) {
		if (size_groups[group_idx].tree_start == NULL_TREE) {
			size_groups[group_idx].tree_start = fields[i];
			size_groups[group_idx].start = i;
			accum_length = 0;
			accum_size = 0;
		}
		accum_size += (unsigned long)int_size_in_bytes(TREE_TYPE(fields[i]));
		accum_length++;
		if (accum_size >= 64) {
			size_groups[group_idx].length = accum_length;
			accum_length = 0;
			group_idx++;
		}
	}

	if (size_groups[group_idx].tree_start != NULL_TREE &&
	    !size_groups[group_idx].length) {
		size_groups[group_idx].length = accum_length;
		group_idx++;
	}

	*num_groups = group_idx;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* blocks; } ;
typedef  TYPE_1__ zend_cfg ;
struct TYPE_5__ {int successors_count; int* successors; } ;
typedef  TYPE_2__ zend_basic_block ;

/* Variables and functions */

__attribute__((used)) static void compute_postnum_recursive(
		int *postnum, int *cur, const zend_cfg *cfg, int block_num) /* {{{ */
{
	int s;
	zend_basic_block *block = &cfg->blocks[block_num];
	if (postnum[block_num] != -1) {
		return;
	}

	postnum[block_num] = -2; /* Marker for "currently visiting" */
	for (s = 0; s < block->successors_count; s++) {
		compute_postnum_recursive(postnum, cur, cfg, block->successors[s]);
	}
	postnum[block_num] = (*cur)++;
}
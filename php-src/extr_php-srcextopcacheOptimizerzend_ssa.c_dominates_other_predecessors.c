#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* predecessors; int /*<<< orphan*/  blocks; } ;
typedef  TYPE_1__ zend_cfg ;
typedef  int zend_bool ;
struct TYPE_6__ {int predecessors_count; int predecessor_offset; } ;
typedef  TYPE_2__ zend_basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  dominates (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static zend_bool dominates_other_predecessors(
		const zend_cfg *cfg, const zend_basic_block *block, int check, int exclude) {
	int i;
	for (i = 0; i < block->predecessors_count; i++) {
		int predecessor = cfg->predecessors[block->predecessor_offset + i];
		if (predecessor != exclude && !dominates(cfg->blocks, check, predecessor)) {
			return 0;
		}
	}
	return 1;
}
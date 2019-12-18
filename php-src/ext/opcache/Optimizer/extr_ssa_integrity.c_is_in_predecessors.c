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
struct TYPE_5__ {int* predecessors; } ;
typedef  TYPE_1__ zend_cfg ;
typedef  int zend_bool ;
struct TYPE_6__ {size_t predecessor_offset; int predecessors_count; } ;
typedef  TYPE_2__ zend_basic_block ;

/* Variables and functions */

__attribute__((used)) static inline zend_bool is_in_predecessors(zend_cfg *cfg, zend_basic_block *block, int check) {
	int i, *predecessors = &cfg->predecessors[block->predecessor_offset];
	for (i = 0; i < block->predecessors_count; i++) {
		if (predecessors[i] == check) {
			return 1;
		}
	}
	return 0;
}
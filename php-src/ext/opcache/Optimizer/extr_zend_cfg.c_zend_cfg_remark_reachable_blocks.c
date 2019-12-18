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
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_5__ {int blocks_count; TYPE_2__* blocks; } ;
typedef  TYPE_1__ zend_cfg ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ zend_basic_block ;

/* Variables and functions */
 int ZEND_BB_REACHABLE ; 
 int /*<<< orphan*/  zend_mark_reachable_blocks (int /*<<< orphan*/  const*,TYPE_1__*,int) ; 

void zend_cfg_remark_reachable_blocks(const zend_op_array *op_array, zend_cfg *cfg) /* {{{ */
{
	zend_basic_block *blocks = cfg->blocks;
	int i;
	int start = 0;

	for (i = 0; i < cfg->blocks_count; i++) {
		if (blocks[i].flags & ZEND_BB_REACHABLE) {
			start = i;
			i++;
			break;
		}
	}

	/* clear all flags */
	for (i = 0; i < cfg->blocks_count; i++) {
		blocks[i].flags = 0;
	}

	zend_mark_reachable_blocks(op_array, cfg, start);
}
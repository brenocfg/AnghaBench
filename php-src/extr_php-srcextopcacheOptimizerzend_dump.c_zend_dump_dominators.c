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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zend_dump_block_info (TYPE_1__ const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_dump_op_array_name (int /*<<< orphan*/  const*) ; 

void zend_dump_dominators(const zend_op_array *op_array, const zend_cfg *cfg)
{
	int j;

	fprintf(stderr, "\nDOMINATORS-TREE for \"");
	zend_dump_op_array_name(op_array);
	fprintf(stderr, "\"\n");
	for (j = 0; j < cfg->blocks_count; j++) {
		zend_basic_block *b = cfg->blocks + j;
		if (b->flags & ZEND_BB_REACHABLE) {
			zend_dump_block_info(cfg, j, 0);
		}
	}
}
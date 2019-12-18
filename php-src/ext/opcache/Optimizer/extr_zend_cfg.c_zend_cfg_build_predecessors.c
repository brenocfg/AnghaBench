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
struct TYPE_4__ {int blocks_count; int edges_count; int* predecessors; TYPE_2__* blocks; } ;
typedef  TYPE_1__ zend_cfg ;
struct TYPE_5__ {size_t predecessors_count; int flags; int successors_count; size_t* successors; int predecessor_offset; } ;
typedef  TYPE_2__ zend_basic_block ;
typedef  int /*<<< orphan*/  zend_arena ;

/* Variables and functions */
 int SUCCESS ; 
 int ZEND_BB_REACHABLE ; 
 scalar_t__ zend_arena_calloc (int /*<<< orphan*/ **,int,int) ; 

int zend_cfg_build_predecessors(zend_arena **arena, zend_cfg *cfg) /* {{{ */
{
	int j, s, edges;
	zend_basic_block *b;
	zend_basic_block *blocks = cfg->blocks;
	zend_basic_block *end = blocks + cfg->blocks_count;
	int *predecessors;

	edges = 0;
	for (b = blocks; b < end; b++) {
		b->predecessors_count = 0;
	}
	for (b = blocks; b < end; b++) {
		if (!(b->flags & ZEND_BB_REACHABLE)) {
			b->successors_count = 0;
			b->predecessors_count = 0;
		} else {
			for (s = 0; s < b->successors_count; s++) {
				edges++;
				blocks[b->successors[s]].predecessors_count++;
			}
		}
	}

	cfg->edges_count = edges;
	cfg->predecessors = predecessors = (int*)zend_arena_calloc(arena, sizeof(int), edges);

	edges = 0;
	for (b = blocks; b < end; b++) {
		if (b->flags & ZEND_BB_REACHABLE) {
			b->predecessor_offset = edges;
			edges += b->predecessors_count;
			b->predecessors_count = 0;
		}
	}

	for (j = 0; j < cfg->blocks_count; j++) {
		if (blocks[j].flags & ZEND_BB_REACHABLE) {
			/* SWITCH_STRING/LONG may have few identical successors */
			for (s = 0; s < blocks[j].successors_count; s++) {
				int duplicate = 0;
				int p;

				for (p = 0; p < s; p++) {
					if (blocks[j].successors[p] == blocks[j].successors[s]) {
						duplicate = 1;
						break;
					}
				}
				if (!duplicate) {
					zend_basic_block *b = blocks + blocks[j].successors[s];

					predecessors[b->predecessor_offset + b->predecessors_count] = j;
					b->predecessors_count++;
				}
			}
		}
	}

	return SUCCESS;
}
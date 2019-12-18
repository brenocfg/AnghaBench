#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int predecessor_offset; int idom; int loop_header; int level; int children; int next_child; scalar_t__ predecessors_count; scalar_t__ successors_count; int /*<<< orphan*/  successors_storage; int /*<<< orphan*/  successors; scalar_t__ flags; } ;
typedef  TYPE_1__ zend_basic_block ;

/* Variables and functions */

__attribute__((used)) static void initialize_block(zend_basic_block *block) {
	block->flags = 0;
	block->successors = block->successors_storage;
	block->successors_count = 0;
	block->predecessors_count = 0;
	block->predecessor_offset = -1;
	block->idom = -1;
	block->loop_header = -1;
	block->level = -1;
	block->children = -1;
	block->next_child = -1;
}
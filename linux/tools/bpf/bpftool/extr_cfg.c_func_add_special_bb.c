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
struct func_node {int /*<<< orphan*/  bbs; } ;
struct bb_node {int /*<<< orphan*/  idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_BLOCK_INDEX ; 
 int /*<<< orphan*/  EXIT_BLOCK_INDEX ; 
 struct bb_node* func_insert_dummy_bb (int /*<<< orphan*/ *) ; 
 TYPE_1__* func_last_bb (struct func_node*) ; 

__attribute__((used)) static bool func_add_special_bb(struct func_node *func)
{
	struct bb_node *bb;

	bb = func_insert_dummy_bb(&func->bbs);
	if (!bb)
		return true;
	bb->idx = ENTRY_BLOCK_INDEX;

	bb = func_insert_dummy_bb(&func_last_bb(func)->l);
	if (!bb)
		return true;
	bb->idx = EXIT_BLOCK_INDEX;

	return false;
}
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
typedef  void* zend_ulong ;
struct TYPE_3__ {void* cur; void* end; int /*<<< orphan*/ * tree; } ;
typedef  TYPE_1__ phpdbg_btree_position ;
typedef  int /*<<< orphan*/  phpdbg_btree ;

/* Variables and functions */

phpdbg_btree_position phpdbg_btree_find_between(phpdbg_btree *tree, zend_ulong lower_idx, zend_ulong higher_idx) {
	phpdbg_btree_position pos;

	pos.tree = tree;
	pos.end = lower_idx;
	pos.cur = higher_idx;

	return pos;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  size_t zend_bool ;
struct TYPE_4__ {struct TYPE_4__** branches; } ;
typedef  TYPE_1__ phpdbg_btree_branch ;

/* Variables and functions */
 int /*<<< orphan*/  pefree (TYPE_1__*,size_t) ; 

void phpdbg_btree_clean_recursive(phpdbg_btree_branch *branch, zend_ulong depth, zend_bool persistent) {
	phpdbg_btree_branch *start = branch;
	while (depth--) {
		zend_bool use_branch = branch + 1 == branch->branches[0];
		if (branch->branches[use_branch]) {
			phpdbg_btree_clean_recursive(branch->branches[use_branch], depth, persistent);
		}
	}

	pefree(start, persistent);
}
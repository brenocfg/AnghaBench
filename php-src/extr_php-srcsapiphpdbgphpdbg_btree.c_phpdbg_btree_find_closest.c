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
typedef  int zend_ulong ;
typedef  int /*<<< orphan*/  phpdbg_btree_result ;
struct TYPE_4__ {int* branches; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ phpdbg_btree_branch ;
struct TYPE_5__ {int depth; TYPE_1__* branch; } ;
typedef  TYPE_2__ phpdbg_btree ;

/* Variables and functions */
 int /*<<< orphan*/  CHOOSE_BRANCH (int) ; 

phpdbg_btree_result *phpdbg_btree_find_closest(phpdbg_btree *tree, zend_ulong idx) {
	phpdbg_btree_branch *branch = tree->branch;
	int i = tree->depth - 1, last_superior_i = -1;

	if (branch == NULL) {
		return NULL;
	}

	/* find nearest watchpoint */
	do {
		if ((idx >> i) % 2 == 0) {
			if (branch->branches[0]) {
				CHOOSE_BRANCH(0);
			/* an impossible branch was found if: */
			} else {
				/* there's no lower branch than idx */
				if (last_superior_i == -1) {
					/* failure */
					return NULL;
				}
				/* reset state */
				branch = tree->branch;
				i = tree->depth - 1;
				/* follow branch according to bits in idx until the last lower branch before the impossible branch */
				do {
					CHOOSE_BRANCH((idx >> i) % 2 == 1 && branch->branches[1]);
				} while (--i > last_superior_i);
				/* use now the lower branch of which we can be sure that it contains only branches lower than idx */
				CHOOSE_BRANCH(0);
				/* and choose the highest possible branch in the branch containing only branches lower than idx */
				while (i--) {
					CHOOSE_BRANCH(branch->branches[1]);
				}
				break;
			}
		/* follow branch according to bits in idx until having found an impossible branch */
		} else {
			if (branch->branches[1]) {
				if (branch->branches[0]) {
					last_superior_i = i;
				}
				CHOOSE_BRANCH(1);
			} else {
				CHOOSE_BRANCH(0);
				while (i--) {
					CHOOSE_BRANCH(branch->branches[1]);
				}
				break;
			}
		}
	} while (i--);

	return &branch->result;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_ulong ;
struct TYPE_7__ {struct TYPE_7__** branches; } ;
typedef  TYPE_1__ phpdbg_btree_branch ;
struct TYPE_8__ {int depth; int /*<<< orphan*/  persistent; TYPE_1__* branch; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ phpdbg_btree ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pefree (TYPE_1__*,int /*<<< orphan*/ ) ; 

int phpdbg_btree_delete(phpdbg_btree *tree, zend_ulong idx) {
	int i = tree->depth;
	phpdbg_btree_branch *branch = tree->branch;
	int i_last_dual_branch = -1, last_dual_branch_branch;
	phpdbg_btree_branch *last_dual_branch = NULL;

	goto check_branch_existence;
	do {
		if (branch->branches[0] && branch->branches[1]) {
			last_dual_branch = branch;
			i_last_dual_branch = i;
			last_dual_branch_branch = (idx >> i) % 2;
		}
		branch = branch->branches[(idx >> i) % 2];

check_branch_existence:
		if (branch == NULL) {
			return FAILURE;
		}
	} while (i--);

	tree->count--;

	if (i_last_dual_branch == -1) {
		pefree(tree->branch, tree->persistent);
		tree->branch = NULL;
	} else {
		if (last_dual_branch->branches[last_dual_branch_branch] == last_dual_branch + 1) {
			phpdbg_btree_branch *original_branch = last_dual_branch->branches[!last_dual_branch_branch];

			memcpy(last_dual_branch + 1, last_dual_branch->branches[!last_dual_branch_branch], (i_last_dual_branch + 1) * sizeof(phpdbg_btree_branch));
			pefree(last_dual_branch->branches[!last_dual_branch_branch], tree->persistent);
			last_dual_branch->branches[!last_dual_branch_branch] = last_dual_branch + 1;

			branch = last_dual_branch->branches[!last_dual_branch_branch];
			for (i = i_last_dual_branch; i--;) {
				branch = (branch->branches[branch->branches[1] == ++original_branch] = last_dual_branch + i_last_dual_branch - i + 1);
			}
		} else {
			pefree(last_dual_branch->branches[last_dual_branch_branch], tree->persistent);
		}

		last_dual_branch->branches[last_dual_branch_branch] = NULL;
	}

	return SUCCESS;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union sidtab_entry_inner {TYPE_3__* ptr_leaf; TYPE_1__* ptr_inner; } ;
typedef  scalar_t__ u32 ;
struct sidtab_convert_params {int (* func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  args; } ;
struct TYPE_6__ {TYPE_2__* entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
struct TYPE_4__ {union sidtab_entry_inner* entries; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SIDTAB_INNER_ENTRIES ; 
 scalar_t__ SIDTAB_LEAF_ENTRIES ; 
 int /*<<< orphan*/  SIDTAB_NODE_ALLOC_SIZE ; 
 int /*<<< orphan*/  cond_resched () ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sidtab_convert_tree(union sidtab_entry_inner *edst,
			       union sidtab_entry_inner *esrc,
			       u32 *pos, u32 count, u32 level,
			       struct sidtab_convert_params *convert)
{
	int rc;
	u32 i;

	if (level != 0) {
		if (!edst->ptr_inner) {
			edst->ptr_inner = kzalloc(SIDTAB_NODE_ALLOC_SIZE,
						  GFP_KERNEL);
			if (!edst->ptr_inner)
				return -ENOMEM;
		}
		i = 0;
		while (i < SIDTAB_INNER_ENTRIES && *pos < count) {
			rc = sidtab_convert_tree(&edst->ptr_inner->entries[i],
						 &esrc->ptr_inner->entries[i],
						 pos, count, level - 1,
						 convert);
			if (rc)
				return rc;
			i++;
		}
	} else {
		if (!edst->ptr_leaf) {
			edst->ptr_leaf = kzalloc(SIDTAB_NODE_ALLOC_SIZE,
						 GFP_KERNEL);
			if (!edst->ptr_leaf)
				return -ENOMEM;
		}
		i = 0;
		while (i < SIDTAB_LEAF_ENTRIES && *pos < count) {
			rc = convert->func(&esrc->ptr_leaf->entries[i].context,
					   &edst->ptr_leaf->entries[i].context,
					   convert->args);
			if (rc)
				return rc;
			(*pos)++;
			i++;
		}
		cond_resched();
	}
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nmatches; } ;
struct tcf_ematch_tree {void* matches; TYPE_2__ hdr; } ;
struct tcf_ematch {TYPE_1__* ops; scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* destroy ) (struct tcf_ematch*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tcf_ematch*) ; 
 struct tcf_ematch* tcf_em_get_match (struct tcf_ematch_tree*,int) ; 
 int /*<<< orphan*/  tcf_em_is_simple (struct tcf_ematch*) ; 

void tcf_em_tree_destroy(struct tcf_ematch_tree *tree)
{
	int i;

	if (tree->matches == NULL)
		return;

	for (i = 0; i < tree->hdr.nmatches; i++) {
		struct tcf_ematch *em = tcf_em_get_match(tree, i);

		if (em->ops) {
			if (em->ops->destroy)
				em->ops->destroy(em);
			else if (!tcf_em_is_simple(em))
				kfree((void *) em->data);
			module_put(em->ops->owner);
		}
	}

	tree->hdr.nmatches = 0;
	kfree(tree->matches);
	tree->matches = NULL;
}
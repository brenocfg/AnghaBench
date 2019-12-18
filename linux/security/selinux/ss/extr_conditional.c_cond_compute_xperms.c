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
struct extended_perms_decision {int dummy; } ;
struct TYPE_2__ {int specified; } ;
struct avtab_node {TYPE_1__ key; } ;
struct avtab_key {int /*<<< orphan*/  specified; } ;
struct avtab {int dummy; } ;

/* Variables and functions */
 int AVTAB_ENABLED ; 
 struct avtab_node* avtab_search_node (struct avtab*,struct avtab_key*) ; 
 struct avtab_node* avtab_search_node_next (struct avtab_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  services_compute_xperms_decision (struct extended_perms_decision*,struct avtab_node*) ; 

void cond_compute_xperms(struct avtab *ctab, struct avtab_key *key,
		struct extended_perms_decision *xpermd)
{
	struct avtab_node *node;

	if (!ctab || !key || !xpermd)
		return;

	for (node = avtab_search_node(ctab, key); node;
			node = avtab_search_node_next(node, key->specified)) {
		if (node->key.specified & AVTAB_ENABLED)
			services_compute_xperms_decision(xpermd, node);
	}
	return;

}
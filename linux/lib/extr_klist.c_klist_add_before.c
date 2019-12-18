#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct klist_node {int /*<<< orphan*/  n_node; } ;
struct klist {int /*<<< orphan*/  k_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  klist_node_init (struct klist*,struct klist_node*) ; 
 struct klist* knode_klist (struct klist_node*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void klist_add_before(struct klist_node *n, struct klist_node *pos)
{
	struct klist *k = knode_klist(pos);

	klist_node_init(k, n);
	spin_lock(&k->k_lock);
	list_add_tail(&n->n_node, &pos->n_node);
	spin_unlock(&k->k_lock);
}
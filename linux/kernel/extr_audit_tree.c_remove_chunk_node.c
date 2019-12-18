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
struct node {struct audit_tree* owner; int /*<<< orphan*/  list; } ;
struct audit_tree {struct audit_chunk* root; int /*<<< orphan*/  same_root; } ;
struct audit_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_tree (struct audit_tree*) ; 

__attribute__((used)) static void remove_chunk_node(struct audit_chunk *chunk, struct node *p)
{
	struct audit_tree *owner = p->owner;

	if (owner->root == chunk) {
		list_del_init(&owner->same_root);
		owner->root = NULL;
	}
	list_del_init(&p->list);
	p->owner = NULL;
	put_tree(owner);
}
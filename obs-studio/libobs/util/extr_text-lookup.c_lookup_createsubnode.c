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
struct text_node {struct text_node* first_subnode; int /*<<< orphan*/  str; struct text_node* next; struct text_leaf* leaf; } ;
struct text_leaf {int dummy; } ;

/* Variables and functions */
 struct text_node* bzalloc (int) ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void lookup_createsubnode(const char *lookup_val, struct text_leaf *leaf,
				 struct text_node *node)
{
	struct text_node *new = bzalloc(sizeof(struct text_node));
	new->leaf = leaf;
	new->next = node->first_subnode;
	dstr_copy(&new->str, lookup_val);

	node->first_subnode = new;
}
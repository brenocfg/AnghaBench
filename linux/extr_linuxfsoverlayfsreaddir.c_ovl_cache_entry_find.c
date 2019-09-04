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
struct rb_root {struct rb_node* rb_node; } ;
struct rb_node {int dummy; } ;
struct TYPE_2__ {struct rb_node* rb_left; struct rb_node* rb_right; } ;
struct ovl_cache_entry {int len; TYPE_1__ node; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct ovl_cache_entry* ovl_cache_entry_from_node (struct rb_node*) ; 
 int strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ovl_cache_entry *ovl_cache_entry_find(struct rb_root *root,
						    const char *name, int len)
{
	struct rb_node *node = root->rb_node;
	int cmp;

	while (node) {
		struct ovl_cache_entry *p = ovl_cache_entry_from_node(node);

		cmp = strncmp(name, p->name, len);
		if (cmp > 0)
			node = p->node.rb_right;
		else if (cmp < 0 || len < p->len)
			node = p->node.rb_left;
		else
			return p;
	}

	return NULL;
}
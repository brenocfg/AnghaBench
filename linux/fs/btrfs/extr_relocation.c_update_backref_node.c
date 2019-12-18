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
typedef  int /*<<< orphan*/  u64 ;
struct rb_node {int dummy; } ;
struct backref_node {int /*<<< orphan*/  rb_node; int /*<<< orphan*/  bytenr; } ;
struct backref_cache {int /*<<< orphan*/  rb_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  backref_tree_panic (struct rb_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rb_node* tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_backref_node(struct backref_cache *cache,
				struct backref_node *node, u64 bytenr)
{
	struct rb_node *rb_node;
	rb_erase(&node->rb_node, &cache->rb_root);
	node->bytenr = bytenr;
	rb_node = tree_insert(&cache->rb_root, node->bytenr, &node->rb_node);
	if (rb_node)
		backref_tree_panic(rb_node, -EEXIST, bytenr);
}
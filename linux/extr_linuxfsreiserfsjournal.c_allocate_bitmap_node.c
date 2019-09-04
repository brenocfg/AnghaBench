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
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct reiserfs_bitmap_node {int /*<<< orphan*/  list; int /*<<< orphan*/  id; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct reiserfs_bitmap_node*) ; 
 struct reiserfs_bitmap_node* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct reiserfs_bitmap_node *allocate_bitmap_node(struct super_block
							 *sb)
{
	struct reiserfs_bitmap_node *bn;
	static int id;

	bn = kmalloc(sizeof(struct reiserfs_bitmap_node), GFP_NOFS);
	if (!bn) {
		return NULL;
	}
	bn->data = kzalloc(sb->s_blocksize, GFP_NOFS);
	if (!bn->data) {
		kfree(bn);
		return NULL;
	}
	bn->id = id++;
	INIT_LIST_HEAD(&bn->list);
	return bn;
}
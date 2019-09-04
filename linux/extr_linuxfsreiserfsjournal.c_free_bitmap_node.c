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
struct super_block {int dummy; } ;
struct reiserfs_journal {scalar_t__ j_free_bitmap_nodes; int /*<<< orphan*/  j_bitmap_nodes; int /*<<< orphan*/  j_used_bitmap_nodes; } ;
struct reiserfs_bitmap_node {int /*<<< orphan*/  list; struct reiserfs_bitmap_node* data; } ;

/* Variables and functions */
 scalar_t__ REISERFS_MAX_BITMAP_NODES ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct reiserfs_bitmap_node*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_bitmap_node(struct super_block *sb,
				    struct reiserfs_bitmap_node *bn)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	journal->j_used_bitmap_nodes--;
	if (journal->j_free_bitmap_nodes > REISERFS_MAX_BITMAP_NODES) {
		kfree(bn->data);
		kfree(bn);
	} else {
		list_add(&bn->list, &journal->j_bitmap_nodes);
		journal->j_free_bitmap_nodes++;
	}
}
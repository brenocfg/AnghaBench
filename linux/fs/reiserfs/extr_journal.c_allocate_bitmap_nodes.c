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
struct reiserfs_journal {int /*<<< orphan*/  j_free_bitmap_nodes; int /*<<< orphan*/  j_bitmap_nodes; } ;
struct reiserfs_bitmap_node {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int REISERFS_MIN_BITMAP_NODES ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 struct reiserfs_bitmap_node* allocate_bitmap_node (struct super_block*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void allocate_bitmap_nodes(struct super_block *sb)
{
	int i;
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	struct reiserfs_bitmap_node *bn = NULL;
	for (i = 0; i < REISERFS_MIN_BITMAP_NODES; i++) {
		bn = allocate_bitmap_node(sb);
		if (bn) {
			list_add(&bn->list, &journal->j_bitmap_nodes);
			journal->j_free_bitmap_nodes++;
		} else {
			/* this is ok, we'll try again when more are needed */
			break;
		}
	}
}
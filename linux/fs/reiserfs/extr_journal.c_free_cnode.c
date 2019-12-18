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
struct reiserfs_journal_cnode {struct reiserfs_journal_cnode* prev; struct reiserfs_journal_cnode* next; } ;
struct reiserfs_journal {struct reiserfs_journal_cnode* j_cnode_free_list; int /*<<< orphan*/  j_cnode_free; int /*<<< orphan*/  j_cnode_used; } ;

/* Variables and functions */
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_check_lock_depth (struct super_block*,char*) ; 

__attribute__((used)) static void free_cnode(struct super_block *sb,
		       struct reiserfs_journal_cnode *cn)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);

	reiserfs_check_lock_depth(sb, "free_cnode");

	journal->j_cnode_used--;
	journal->j_cnode_free++;
	/* memset(cn, 0, sizeof(struct reiserfs_journal_cnode)) ; */
	cn->next = journal->j_cnode_free_list;
	if (journal->j_cnode_free_list) {
		journal->j_cnode_free_list->prev = cn;
	}
	cn->prev = NULL;	/* not needed with the memset, but I might kill the memset, and forget to do this */
	journal->j_cnode_free_list = cn;
}
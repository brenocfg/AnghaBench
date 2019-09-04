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
struct reiserfs_journal_cnode {struct reiserfs_journal_cnode* next; int /*<<< orphan*/ * prev; } ;
struct reiserfs_journal {scalar_t__ j_cnode_free; struct reiserfs_journal_cnode* j_cnode_free_list; int /*<<< orphan*/  j_cnode_used; } ;

/* Variables and functions */
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  memset (struct reiserfs_journal_cnode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_check_lock_depth (struct super_block*,char*) ; 

__attribute__((used)) static struct reiserfs_journal_cnode *get_cnode(struct super_block *sb)
{
	struct reiserfs_journal_cnode *cn;
	struct reiserfs_journal *journal = SB_JOURNAL(sb);

	reiserfs_check_lock_depth(sb, "get_cnode");

	if (journal->j_cnode_free <= 0) {
		return NULL;
	}
	journal->j_cnode_used++;
	journal->j_cnode_free--;
	cn = journal->j_cnode_free_list;
	if (!cn) {
		return cn;
	}
	if (cn->next) {
		cn->next->prev = NULL;
	}
	journal->j_cnode_free_list = cn->next;
	memset(cn, 0, sizeof(struct reiserfs_journal_cnode));
	return cn;
}
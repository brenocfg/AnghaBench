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
struct reiserfs_journal_list {unsigned int j_trans_id; } ;
struct list_head {int /*<<< orphan*/  next; } ;
struct reiserfs_journal {struct list_head j_journal_list; } ;

/* Variables and functions */
 struct reiserfs_journal_list* JOURNAL_LIST_ENTRY (int /*<<< orphan*/ ) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

__attribute__((used)) static int journal_list_still_alive(struct super_block *s,
				    unsigned int trans_id)
{
	struct reiserfs_journal *journal = SB_JOURNAL(s);
	struct list_head *entry = &journal->j_journal_list;
	struct reiserfs_journal_list *jl;

	if (!list_empty(entry)) {
		jl = JOURNAL_LIST_ENTRY(entry->next);
		if (jl->j_trans_id <= trans_id) {
			return 1;
		}
	}
	return 0;
}
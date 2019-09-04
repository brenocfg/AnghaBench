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
struct reiserfs_journal_cnode {int dummy; } ;
struct reiserfs_journal {int /*<<< orphan*/  j_hash_table; } ;

/* Variables and functions */
 int JOURNAL_HASH_SIZE ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_journal_hash(struct super_block *sb)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	memset(journal->j_hash_table, 0,
	       JOURNAL_HASH_SIZE * sizeof(struct reiserfs_journal_cnode *));
}
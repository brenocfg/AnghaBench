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
struct tree_balance {int* blknum; struct buffer_head** S_new; struct buffer_head** snum; } ;
struct item_head {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  B_BLK_HEAD (struct buffer_head*) ; 
 int /*<<< orphan*/  DISK_LEAF_NODE_LEVEL ; 
 int /*<<< orphan*/  KEY_SIZE ; 
 int M_INSERT ; 
 int M_PASTE ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,struct buffer_head*) ; 
 int /*<<< orphan*/  balance_leaf_new_nodes_insert (struct tree_balance*,struct item_head* const,char const* const,struct item_head*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  balance_leaf_new_nodes_paste (struct tree_balance*,struct item_head* const,char const* const,struct item_head*,struct buffer_head**,int) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_journal_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_journaled (struct buffer_head*) ; 
 struct buffer_head* get_FEB (struct tree_balance*) ; 
 int /*<<< orphan*/  leaf_key (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct item_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_blkh_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_new_nodes(struct tree_balance *tb,
				   struct item_head * const ih,
				   const char * const body,
				   struct item_head *insert_key,
				   struct buffer_head **insert_ptr,
				   int flag)
{
	int i;
	for (i = tb->blknum[0] - 2; i >= 0; i--) {
		BUG_ON(flag != M_INSERT && flag != M_PASTE);

		RFALSE(!tb->snum[i],
		       "PAP-12200: snum[%d] == %d. Must be > 0", i,
		       tb->snum[i]);

		/* here we shift from S to S_new nodes */

		tb->S_new[i] = get_FEB(tb);

		/* initialized block type and tree level */
		set_blkh_level(B_BLK_HEAD(tb->S_new[i]), DISK_LEAF_NODE_LEVEL);

		if (flag == M_INSERT)
			balance_leaf_new_nodes_insert(tb, ih, body, insert_key,
						      insert_ptr, i);
		else /* M_PASTE */
			balance_leaf_new_nodes_paste(tb, ih, body, insert_key,
						     insert_ptr, i);

		memcpy(insert_key + i, leaf_key(tb->S_new[i], 0), KEY_SIZE);
		insert_ptr[i] = tb->S_new[i];

		RFALSE(!buffer_journaled(tb->S_new[i])
		       || buffer_journal_dirty(tb->S_new[i])
		       || buffer_dirty(tb->S_new[i]),
		       "PAP-12247: S_new[%d] : (%b)",
		       i, tb->S_new[i]);
	}
}
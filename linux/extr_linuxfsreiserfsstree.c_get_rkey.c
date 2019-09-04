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
struct treepath {int path_length; } ;
struct super_block {int dummy; } ;
struct reiserfs_key {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_IS_IN_TREE (struct buffer_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 scalar_t__ B_N_CHILD_NUM (struct buffer_head*,int) ; 
 int FIRST_PATH_ELEMENT_OFFSET ; 
 struct reiserfs_key const MAX_KEY ; 
 struct reiserfs_key const MIN_KEY ; 
 struct buffer_head* PATH_OFFSET_PBUFFER (struct treepath const*,int) ; 
 int PATH_OFFSET_POSITION (struct treepath const*,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 scalar_t__ SB_ROOT_BLOCK (struct super_block const*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 struct reiserfs_key const* internal_key (struct buffer_head*,int) ; 

inline const struct reiserfs_key *get_rkey(const struct treepath *chk_path,
					   const struct super_block *sb)
{
	int position, path_offset = chk_path->path_length;
	struct buffer_head *parent;

	RFALSE(path_offset < FIRST_PATH_ELEMENT_OFFSET,
	       "PAP-5030: invalid offset in the path");

	while (path_offset-- > FIRST_PATH_ELEMENT_OFFSET) {

		RFALSE(!buffer_uptodate
		       (PATH_OFFSET_PBUFFER(chk_path, path_offset)),
		       "PAP-5040: parent is not uptodate");

		/* Parent at the path is not in the tree now. */
		if (!B_IS_IN_TREE
		    (parent =
		     PATH_OFFSET_PBUFFER(chk_path, path_offset)))
			return &MIN_KEY;
		/* Check whether position in the parent is correct. */
		if ((position =
		     PATH_OFFSET_POSITION(chk_path,
					  path_offset)) >
		    B_NR_ITEMS(parent))
			return &MIN_KEY;
		/*
		 * Check whether parent at the path really points
		 * to the child.
		 */
		if (B_N_CHILD_NUM(parent, position) !=
		    PATH_OFFSET_PBUFFER(chk_path,
					path_offset + 1)->b_blocknr)
			return &MIN_KEY;

		/*
		 * Return delimiting key if position in the parent
		 * is not the last one.
		 */
		if (position != B_NR_ITEMS(parent))
			return internal_key(parent, position);
	}

	/* Return MAX_KEY if we are in the root of the buffer tree. */
	if (PATH_OFFSET_PBUFFER(chk_path, FIRST_PATH_ELEMENT_OFFSET)->
	    b_blocknr == SB_ROOT_BLOCK(sb))
		return &MAX_KEY;
	return &MIN_KEY;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct treepath {int dummy; } ;
struct tree_balance {int* lkey; int* rkey; int /*<<< orphan*/  tb_sb; struct treepath* tb_path; } ;
struct cpu_key {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;
struct TYPE_6__ {int path_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_IS_IN_TREE (struct buffer_head*) ; 
 int B_LEVEL (struct buffer_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 scalar_t__ B_N_CHILD_NUM (struct buffer_head*,int) ; 
 int CARRY_ON ; 
 int DISK_LEAF_NODE_LEVEL ; 
 scalar_t__ FILESYSTEM_CHANGED_TB (struct tree_balance*) ; 
 int FIRST_PATH_ELEMENT_OFFSET ; 
 int /*<<< orphan*/  INITIALIZE_PATH (TYPE_1__) ; 
 int INT_MAX ; 
 scalar_t__ IO_ERROR ; 
 char LEFT_PARENTS ; 
 int PATH_H_PATH_OFFSET (struct treepath*,int) ; 
 struct buffer_head* PATH_OFFSET_PBUFFER (struct treepath*,int) ; 
 int PATH_OFFSET_POSITION (struct treepath*,int) ; 
 struct buffer_head* PATH_PLAST_BUFFER (TYPE_1__*) ; 
 int REPEAT_SEARCH ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 char RIGHT_PARENTS ; 
 scalar_t__ SB_ROOT_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wait_on_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  decrement_key (struct cpu_key*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  internal_key (struct buffer_head*,int) ; 
 int /*<<< orphan*/  le_key2cpu_key (struct cpu_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathrelse (TYPE_1__*) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (int /*<<< orphan*/ ,int) ; 
 int reiserfs_write_unlock_nested (int /*<<< orphan*/ ) ; 
 TYPE_1__ s_path_to_neighbor_father ; 
 scalar_t__ search_by_key (int /*<<< orphan*/ ,struct cpu_key*,TYPE_1__*,int) ; 

__attribute__((used)) static int get_far_parent(struct tree_balance *tb,
			  int h,
			  struct buffer_head **pfather,
			  struct buffer_head **pcom_father, char c_lr_par)
{
	struct buffer_head *parent;
	INITIALIZE_PATH(s_path_to_neighbor_father);
	struct treepath *path = tb->tb_path;
	struct cpu_key s_lr_father_key;
	int counter,
	    position = INT_MAX,
	    first_last_position = 0,
	    path_offset = PATH_H_PATH_OFFSET(path, h);

	/*
	 * Starting from F[h] go upwards in the tree, and look for the common
	 * ancestor of F[h], and its neighbor l/r, that should be obtained.
	 */

	counter = path_offset;

	RFALSE(counter < FIRST_PATH_ELEMENT_OFFSET,
	       "PAP-8180: invalid path length");

	for (; counter > FIRST_PATH_ELEMENT_OFFSET; counter--) {
		/*
		 * Check whether parent of the current buffer in the path
		 * is really parent in the tree.
		 */
		if (!B_IS_IN_TREE
		    (parent = PATH_OFFSET_PBUFFER(path, counter - 1)))
			return REPEAT_SEARCH;

		/* Check whether position in the parent is correct. */
		if ((position =
		     PATH_OFFSET_POSITION(path,
					  counter - 1)) >
		    B_NR_ITEMS(parent))
			return REPEAT_SEARCH;

		/*
		 * Check whether parent at the path really points
		 * to the child.
		 */
		if (B_N_CHILD_NUM(parent, position) !=
		    PATH_OFFSET_PBUFFER(path, counter)->b_blocknr)
			return REPEAT_SEARCH;

		/*
		 * Return delimiting key if position in the parent is not
		 * equal to first/last one.
		 */
		if (c_lr_par == RIGHT_PARENTS)
			first_last_position = B_NR_ITEMS(parent);
		if (position != first_last_position) {
			*pcom_father = parent;
			get_bh(*pcom_father);
			/*(*pcom_father = parent)->b_count++; */
			break;
		}
	}

	/* if we are in the root of the tree, then there is no common father */
	if (counter == FIRST_PATH_ELEMENT_OFFSET) {
		/*
		 * Check whether first buffer in the path is the
		 * root of the tree.
		 */
		if (PATH_OFFSET_PBUFFER
		    (tb->tb_path,
		     FIRST_PATH_ELEMENT_OFFSET)->b_blocknr ==
		    SB_ROOT_BLOCK(tb->tb_sb)) {
			*pfather = *pcom_father = NULL;
			return CARRY_ON;
		}
		return REPEAT_SEARCH;
	}

	RFALSE(B_LEVEL(*pcom_father) <= DISK_LEAF_NODE_LEVEL,
	       "PAP-8185: (%b %z) level too small",
	       *pcom_father, *pcom_father);

	/* Check whether the common parent is locked. */

	if (buffer_locked(*pcom_father)) {

		/* Release the write lock while the buffer is busy */
		int depth = reiserfs_write_unlock_nested(tb->tb_sb);
		__wait_on_buffer(*pcom_father);
		reiserfs_write_lock_nested(tb->tb_sb, depth);
		if (FILESYSTEM_CHANGED_TB(tb)) {
			brelse(*pcom_father);
			return REPEAT_SEARCH;
		}
	}

	/*
	 * So, we got common parent of the current node and its
	 * left/right neighbor.  Now we are getting the parent of the
	 * left/right neighbor.
	 */

	/* Form key to get parent of the left/right neighbor. */
	le_key2cpu_key(&s_lr_father_key,
		       internal_key(*pcom_father,
				      (c_lr_par ==
				       LEFT_PARENTS) ? (tb->lkey[h - 1] =
							position -
							1) : (tb->rkey[h -
									   1] =
							      position)));

	if (c_lr_par == LEFT_PARENTS)
		decrement_key(&s_lr_father_key);

	if (search_by_key
	    (tb->tb_sb, &s_lr_father_key, &s_path_to_neighbor_father,
	     h + 1) == IO_ERROR)
		/* path is released */
		return IO_ERROR;

	if (FILESYSTEM_CHANGED_TB(tb)) {
		pathrelse(&s_path_to_neighbor_father);
		brelse(*pcom_father);
		return REPEAT_SEARCH;
	}

	*pfather = PATH_PLAST_BUFFER(&s_path_to_neighbor_father);

	RFALSE(B_LEVEL(*pfather) != h + 1,
	       "PAP-8190: (%b %z) level too small", *pfather, *pfather);
	RFALSE(s_path_to_neighbor_father.path_length <
	       FIRST_PATH_ELEMENT_OFFSET, "PAP-8192: path length is too small");

	s_path_to_neighbor_father.path_length--;
	pathrelse(&s_path_to_neighbor_father);
	return CARRY_ON;
}
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
struct virtual_node {int vn_size; int vn_nr_item; scalar_t__ vn_mode; scalar_t__ vn_free_ptr; int vn_affected_item_num; struct virtual_item* vn_vi; int /*<<< orphan*/  vn_data; struct item_head* vn_ins_ih; } ;
struct virtual_item {int vi_item_len; scalar_t__ vi_uarea; int /*<<< orphan*/  vi_type; int /*<<< orphan*/  vi_item; struct item_head* vi_ih; int /*<<< orphan*/  vi_new_data; } ;
struct tree_balance {int* insert_size; scalar_t__ vn_buf; scalar_t__ vn_buf_size; int /*<<< orphan*/ * rkey; scalar_t__* CFR; int /*<<< orphan*/  tb_sb; struct virtual_node* tb_vn; int /*<<< orphan*/  tb_path; } ;
struct reiserfs_key {int dummy; } ;
struct item_head {struct reiserfs_key ih_key; } ;
struct buffer_head {int /*<<< orphan*/  b_size; } ;

/* Variables and functions */
 int B_FREE_SPACE (struct buffer_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 int DC_SIZE ; 
 scalar_t__ IH_SIZE ; 
 int KEY_SIZE ; 
 int MAX_CHILD_SIZE (struct buffer_head*) ; 
 scalar_t__ M_CUT ; 
 scalar_t__ M_DELETE ; 
 scalar_t__ M_INSERT ; 
 scalar_t__ M_PASTE ; 
 struct buffer_head* PATH_H_PBUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFALSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VI_TYPE_LEFT_MERGEABLE ; 
 int /*<<< orphan*/  VI_TYPE_RIGHT_MERGEABLE ; 
 int /*<<< orphan*/  ih_item_body (struct buffer_head*,struct item_head*) ; 
 scalar_t__ ih_item_len (struct item_head*) ; 
 struct reiserfs_key* internal_key (scalar_t__,int /*<<< orphan*/ ) ; 
 struct item_head* item_head (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct virtual_item*,int /*<<< orphan*/ ,int) ; 
 int old_item_num (int,int,scalar_t__) ; 
 scalar_t__ op_create_vi (struct virtual_node*,struct virtual_item*,int,int) ; 
 scalar_t__ op_is_left_mergeable (struct reiserfs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void create_virtual_node(struct tree_balance *tb, int h)
{
	struct item_head *ih;
	struct virtual_node *vn = tb->tb_vn;
	int new_num;
	struct buffer_head *Sh;	/* this comes from tb->S[h] */

	Sh = PATH_H_PBUFFER(tb->tb_path, h);

	/* size of changed node */
	vn->vn_size =
	    MAX_CHILD_SIZE(Sh) - B_FREE_SPACE(Sh) + tb->insert_size[h];

	/* for internal nodes array if virtual items is not created */
	if (h) {
		vn->vn_nr_item = (vn->vn_size - DC_SIZE) / (DC_SIZE + KEY_SIZE);
		return;
	}

	/* number of items in virtual node  */
	vn->vn_nr_item =
	    B_NR_ITEMS(Sh) + ((vn->vn_mode == M_INSERT) ? 1 : 0) -
	    ((vn->vn_mode == M_DELETE) ? 1 : 0);

	/* first virtual item */
	vn->vn_vi = (struct virtual_item *)(tb->tb_vn + 1);
	memset(vn->vn_vi, 0, vn->vn_nr_item * sizeof(struct virtual_item));
	vn->vn_free_ptr += vn->vn_nr_item * sizeof(struct virtual_item);

	/* first item in the node */
	ih = item_head(Sh, 0);

	/* define the mergeability for 0-th item (if it is not being deleted) */
	if (op_is_left_mergeable(&ih->ih_key, Sh->b_size)
	    && (vn->vn_mode != M_DELETE || vn->vn_affected_item_num))
		vn->vn_vi[0].vi_type |= VI_TYPE_LEFT_MERGEABLE;

	/*
	 * go through all items that remain in the virtual
	 * node (except for the new (inserted) one)
	 */
	for (new_num = 0; new_num < vn->vn_nr_item; new_num++) {
		int j;
		struct virtual_item *vi = vn->vn_vi + new_num;
		int is_affected =
		    ((new_num != vn->vn_affected_item_num) ? 0 : 1);

		if (is_affected && vn->vn_mode == M_INSERT)
			continue;

		/* get item number in source node */
		j = old_item_num(new_num, vn->vn_affected_item_num,
				 vn->vn_mode);

		vi->vi_item_len += ih_item_len(ih + j) + IH_SIZE;
		vi->vi_ih = ih + j;
		vi->vi_item = ih_item_body(Sh, ih + j);
		vi->vi_uarea = vn->vn_free_ptr;

		/*
		 * FIXME: there is no check that item operation did not
		 * consume too much memory
		 */
		vn->vn_free_ptr +=
		    op_create_vi(vn, vi, is_affected, tb->insert_size[0]);
		if (tb->vn_buf + tb->vn_buf_size < vn->vn_free_ptr)
			reiserfs_panic(tb->tb_sb, "vs-8030",
				       "virtual node space consumed");

		if (!is_affected)
			/* this is not being changed */
			continue;

		if (vn->vn_mode == M_PASTE || vn->vn_mode == M_CUT) {
			vn->vn_vi[new_num].vi_item_len += tb->insert_size[0];
			/* pointer to data which is going to be pasted */
			vi->vi_new_data = vn->vn_data;
		}
	}

	/* virtual inserted item is not defined yet */
	if (vn->vn_mode == M_INSERT) {
		struct virtual_item *vi = vn->vn_vi + vn->vn_affected_item_num;

		RFALSE(vn->vn_ins_ih == NULL,
		       "vs-8040: item header of inserted item is not specified");
		vi->vi_item_len = tb->insert_size[0];
		vi->vi_ih = vn->vn_ins_ih;
		vi->vi_item = vn->vn_data;
		vi->vi_uarea = vn->vn_free_ptr;

		op_create_vi(vn, vi, 0 /*not pasted or cut */ ,
			     tb->insert_size[0]);
	}

	/*
	 * set right merge flag we take right delimiting key and
	 * check whether it is a mergeable item
	 */
	if (tb->CFR[0]) {
		struct reiserfs_key *key;

		key = internal_key(tb->CFR[0], tb->rkey[0]);
		if (op_is_left_mergeable(key, Sh->b_size)
		    && (vn->vn_mode != M_DELETE
			|| vn->vn_affected_item_num != B_NR_ITEMS(Sh) - 1))
			vn->vn_vi[vn->vn_nr_item - 1].vi_type |=
			    VI_TYPE_RIGHT_MERGEABLE;

#ifdef CONFIG_REISERFS_CHECK
		if (op_is_left_mergeable(key, Sh->b_size) &&
		    !(vn->vn_mode != M_DELETE
		      || vn->vn_affected_item_num != B_NR_ITEMS(Sh) - 1)) {
			/*
			 * we delete last item and it could be merged
			 * with right neighbor's first item
			 */
			if (!
			    (B_NR_ITEMS(Sh) == 1
			     && is_direntry_le_ih(item_head(Sh, 0))
			     && ih_entry_count(item_head(Sh, 0)) == 1)) {
				/*
				 * node contains more than 1 item, or item
				 * is not directory item, or this item
				 * contains more than 1 entry
				 */
				print_block(Sh, 0, -1, -1);
				reiserfs_panic(tb->tb_sb, "vs-8045",
					       "rdkey %k, affected item==%d "
					       "(mode==%c) Must be %c",
					       key, vn->vn_affected_item_num,
					       vn->vn_mode, M_DELETE);
			}
		}
#endif

	}
}
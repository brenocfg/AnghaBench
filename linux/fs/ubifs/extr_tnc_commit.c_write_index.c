#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ubifs_znode {int child_cnt; int level; size_t ciip; size_t iip; int lnum; int offs; int len; int /*<<< orphan*/  flags; struct ubifs_znode* cnext; TYPE_6__* parent; TYPE_4__* cparent; struct ubifs_zbranch* zbranch; } ;
struct ubifs_zbranch {struct ubifs_znode* znode; int /*<<< orphan*/  len; int /*<<< orphan*/  lnum; int /*<<< orphan*/ * hash; int /*<<< orphan*/  offs; int /*<<< orphan*/  key; } ;
struct TYPE_14__ {int /*<<< orphan*/  hash; } ;
struct ubifs_info {int ihead_lnum; int ihead_offs; int max_idx_node_sz; int min_io_size; int leb_size; int* ilebs; TYPE_1__* dbg; struct ubifs_idx_node* cbuf; struct ubifs_znode* cnext; int /*<<< orphan*/  tnc_mutex; TYPE_7__ zroot; struct ubifs_znode* enext; } ;
struct TYPE_9__ {int /*<<< orphan*/  node_type; } ;
struct ubifs_idx_node {void* level; void* child_cnt; TYPE_2__ ch; } ;
struct ubifs_branch {void* len; void* offs; void* lnum; int /*<<< orphan*/  key; } ;
struct TYPE_13__ {TYPE_5__* zbranch; } ;
struct TYPE_12__ {int /*<<< orphan*/  hash; } ;
struct TYPE_11__ {TYPE_3__* zbranch; } ;
struct TYPE_10__ {int /*<<< orphan*/  hash; } ;
struct TYPE_8__ {int new_ihead_lnum; int new_ihead_offs; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  COW_ZNODE ; 
 int /*<<< orphan*/  DIRTY_ZNODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  LPROPS_NC ; 
 int /*<<< orphan*/  LPROPS_TAKEN ; 
 int UBIFS_HASH_ARR_SZ ; 
 int /*<<< orphan*/  UBIFS_IDX_NODE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_write_idx (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (struct ubifs_idx_node*,struct ubifs_idx_node*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_branch_hash (struct ubifs_info*,struct ubifs_branch*) ; 
 int /*<<< orphan*/  ubifs_copy_hash (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_dump_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*) ; 
 struct ubifs_branch* ubifs_idx_branch (struct ubifs_info*,struct ubifs_idx_node*,int) ; 
 int ubifs_idx_node_sz (struct ubifs_info*,int) ; 
 int ubifs_leb_write (struct ubifs_info*,int,struct ubifs_idx_node*,int,int) ; 
 int /*<<< orphan*/  ubifs_node_calc_hash (struct ubifs_info*,struct ubifs_idx_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_pad (struct ubifs_info*,struct ubifs_idx_node*,int) ; 
 int /*<<< orphan*/  ubifs_prepare_node (struct ubifs_info*,struct ubifs_idx_node*,int,int /*<<< orphan*/ ) ; 
 int ubifs_update_one_lp (struct ubifs_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_zn_cow (struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_zn_obsolete (struct ubifs_znode*) ; 

__attribute__((used)) static int write_index(struct ubifs_info *c)
{
	struct ubifs_idx_node *idx;
	struct ubifs_znode *znode, *cnext;
	int i, lnum, offs, len, next_len, buf_len, buf_offs, used;
	int avail, wlen, err, lnum_pos = 0, blen, nxt_offs;

	cnext = c->enext;
	if (!cnext)
		return 0;

	/*
	 * Always write index nodes to the index head so that index nodes and
	 * other types of nodes are never mixed in the same erase block.
	 */
	lnum = c->ihead_lnum;
	buf_offs = c->ihead_offs;

	/* Allocate commit buffer */
	buf_len = ALIGN(c->max_idx_node_sz, c->min_io_size);
	used = 0;
	avail = buf_len;

	/* Ensure there is enough room for first write */
	next_len = ubifs_idx_node_sz(c, cnext->child_cnt);
	if (buf_offs + next_len > c->leb_size) {
		err = ubifs_update_one_lp(c, lnum, LPROPS_NC, 0, 0,
					  LPROPS_TAKEN);
		if (err)
			return err;
		lnum = -1;
	}

	while (1) {
		u8 hash[UBIFS_HASH_ARR_SZ];

		cond_resched();

		znode = cnext;
		idx = c->cbuf + used;

		/* Make index node */
		idx->ch.node_type = UBIFS_IDX_NODE;
		idx->child_cnt = cpu_to_le16(znode->child_cnt);
		idx->level = cpu_to_le16(znode->level);
		for (i = 0; i < znode->child_cnt; i++) {
			struct ubifs_branch *br = ubifs_idx_branch(c, idx, i);
			struct ubifs_zbranch *zbr = &znode->zbranch[i];

			key_write_idx(c, &zbr->key, &br->key);
			br->lnum = cpu_to_le32(zbr->lnum);
			br->offs = cpu_to_le32(zbr->offs);
			br->len = cpu_to_le32(zbr->len);
			ubifs_copy_hash(c, zbr->hash, ubifs_branch_hash(c, br));
			if (!zbr->lnum || !zbr->len) {
				ubifs_err(c, "bad ref in znode");
				ubifs_dump_znode(c, znode);
				if (zbr->znode)
					ubifs_dump_znode(c, zbr->znode);

				return -EINVAL;
			}
		}
		len = ubifs_idx_node_sz(c, znode->child_cnt);
		ubifs_prepare_node(c, idx, len, 0);
		ubifs_node_calc_hash(c, idx, hash);

		mutex_lock(&c->tnc_mutex);

		if (znode->cparent)
			ubifs_copy_hash(c, hash,
					znode->cparent->zbranch[znode->ciip].hash);

		if (znode->parent) {
			if (!ubifs_zn_obsolete(znode))
				ubifs_copy_hash(c, hash,
					znode->parent->zbranch[znode->iip].hash);
		} else {
			ubifs_copy_hash(c, hash, c->zroot.hash);
		}

		mutex_unlock(&c->tnc_mutex);

		/* Determine the index node position */
		if (lnum == -1) {
			lnum = c->ilebs[lnum_pos++];
			buf_offs = 0;
			used = 0;
			avail = buf_len;
		}
		offs = buf_offs + used;

		if (lnum != znode->lnum || offs != znode->offs ||
		    len != znode->len) {
			ubifs_err(c, "inconsistent znode posn");
			return -EINVAL;
		}

		/* Grab some stuff from znode while we still can */
		cnext = znode->cnext;

		ubifs_assert(c, ubifs_zn_dirty(znode));
		ubifs_assert(c, ubifs_zn_cow(znode));

		/*
		 * It is important that other threads should see %DIRTY_ZNODE
		 * flag cleared before %COW_ZNODE. Specifically, it matters in
		 * the 'dirty_cow_znode()' function. This is the reason for the
		 * first barrier. Also, we want the bit changes to be seen to
		 * other threads ASAP, to avoid unnecesarry copying, which is
		 * the reason for the second barrier.
		 */
		clear_bit(DIRTY_ZNODE, &znode->flags);
		smp_mb__before_atomic();
		clear_bit(COW_ZNODE, &znode->flags);
		smp_mb__after_atomic();

		/*
		 * We have marked the znode as clean but have not updated the
		 * @c->clean_zn_cnt counter. If this znode becomes dirty again
		 * before 'free_obsolete_znodes()' is called, then
		 * @c->clean_zn_cnt will be decremented before it gets
		 * incremented (resulting in 2 decrements for the same znode).
		 * This means that @c->clean_zn_cnt may become negative for a
		 * while.
		 *
		 * Q: why we cannot increment @c->clean_zn_cnt?
		 * A: because we do not have the @c->tnc_mutex locked, and the
		 *    following code would be racy and buggy:
		 *
		 *    if (!ubifs_zn_obsolete(znode)) {
		 *            atomic_long_inc(&c->clean_zn_cnt);
		 *            atomic_long_inc(&ubifs_clean_zn_cnt);
		 *    }
		 *
		 *    Thus, we just delay the @c->clean_zn_cnt update until we
		 *    have the mutex locked.
		 */

		/* Do not access znode from this point on */

		/* Update buffer positions */
		wlen = used + len;
		used += ALIGN(len, 8);
		avail -= ALIGN(len, 8);

		/*
		 * Calculate the next index node length to see if there is
		 * enough room for it
		 */
		if (cnext == c->cnext)
			next_len = 0;
		else
			next_len = ubifs_idx_node_sz(c, cnext->child_cnt);

		nxt_offs = buf_offs + used + next_len;
		if (next_len && nxt_offs <= c->leb_size) {
			if (avail > 0)
				continue;
			else
				blen = buf_len;
		} else {
			wlen = ALIGN(wlen, 8);
			blen = ALIGN(wlen, c->min_io_size);
			ubifs_pad(c, c->cbuf + wlen, blen - wlen);
		}

		/* The buffer is full or there are no more znodes to do */
		err = ubifs_leb_write(c, lnum, c->cbuf, buf_offs, blen);
		if (err)
			return err;
		buf_offs += blen;
		if (next_len) {
			if (nxt_offs > c->leb_size) {
				err = ubifs_update_one_lp(c, lnum, LPROPS_NC, 0,
							  0, LPROPS_TAKEN);
				if (err)
					return err;
				lnum = -1;
			}
			used -= blen;
			if (used < 0)
				used = 0;
			avail = buf_len - used;
			memmove(c->cbuf, c->cbuf + blen, used);
			continue;
		}
		break;
	}

	if (lnum != c->dbg->new_ihead_lnum ||
	    buf_offs != c->dbg->new_ihead_offs) {
		ubifs_err(c, "inconsistent ihead");
		return -EINVAL;
	}

	c->ihead_lnum = lnum;
	c->ihead_offs = buf_offs;

	return 0;
}
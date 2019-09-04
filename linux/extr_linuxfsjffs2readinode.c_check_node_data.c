#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct jffs2_tmp_dnode_info {int csize; int data_crc; int /*<<< orphan*/  partial_crc; TYPE_1__* fn; } ;
struct jffs2_sb_info {int wbuf_pagesize; size_t sector_size; int used_size; int unchecked_size; int /*<<< orphan*/  mtd; int /*<<< orphan*/  erase_completion_lock; struct jffs2_eraseblock* blocks; } ;
struct jffs2_raw_node_ref {size_t flash_offset; } ;
struct jffs2_raw_inode {int dummy; } ;
struct jffs2_eraseblock {int used_size; int unchecked_size; } ;
struct TYPE_2__ {struct jffs2_raw_node_ref* raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  JFFS2_ERROR (char*,int,size_t,int) ; 
 int /*<<< orphan*/  JFFS2_NOTICE (char*,int,int,int) ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,int,...) ; 
 size_t REF_PRISTINE ; 
 int crc32 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  dbg_readinode (char*,int,int,int,...) ; 
 int /*<<< orphan*/  jffs2_dbg_acct_paranoia_check_nolock (struct jffs2_sb_info*,struct jffs2_eraseblock*) ; 
 int jffs2_flash_read (struct jffs2_sb_info*,int,int,size_t*,unsigned char*) ; 
 scalar_t__ jffs2_is_writebuffered (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int mtd_point (int /*<<< orphan*/ ,int,int,size_t*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtd_unpoint (int /*<<< orphan*/ ,int,int) ; 
 int ref_offset (struct jffs2_raw_node_ref*) ; 
 int ref_totlen (struct jffs2_sb_info*,struct jffs2_eraseblock*,struct jffs2_raw_node_ref*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int check_node_data(struct jffs2_sb_info *c, struct jffs2_tmp_dnode_info *tn)
{
	struct jffs2_raw_node_ref *ref = tn->fn->raw;
	int err = 0, pointed = 0;
	struct jffs2_eraseblock *jeb;
	unsigned char *buffer;
	uint32_t crc, ofs, len;
	size_t retlen;

	BUG_ON(tn->csize == 0);

	/* Calculate how many bytes were already checked */
	ofs = ref_offset(ref) + sizeof(struct jffs2_raw_inode);
	len = tn->csize;

	if (jffs2_is_writebuffered(c)) {
		int adj = ofs % c->wbuf_pagesize;
		if (likely(adj))
			adj = c->wbuf_pagesize - adj;

		if (adj >= tn->csize) {
			dbg_readinode("no need to check node at %#08x, data length %u, data starts at %#08x - it has already been checked.\n",
				      ref_offset(ref), tn->csize, ofs);
			goto adj_acc;
		}

		ofs += adj;
		len -= adj;
	}

	dbg_readinode("check node at %#08x, data length %u, partial CRC %#08x, correct CRC %#08x, data starts at %#08x, start checking from %#08x - %u bytes.\n",
		ref_offset(ref), tn->csize, tn->partial_crc, tn->data_crc, ofs - len, ofs, len);

#ifndef __ECOS
	/* TODO: instead, incapsulate point() stuff to jffs2_flash_read(),
	 * adding and jffs2_flash_read_end() interface. */
	err = mtd_point(c->mtd, ofs, len, &retlen, (void **)&buffer, NULL);
	if (!err && retlen < len) {
		JFFS2_WARNING("MTD point returned len too short: %zu instead of %u.\n", retlen, tn->csize);
		mtd_unpoint(c->mtd, ofs, retlen);
	} else if (err) {
		if (err != -EOPNOTSUPP)
			JFFS2_WARNING("MTD point failed: error code %d.\n", err);
	} else
		pointed = 1; /* succefully pointed to device */
#endif

	if (!pointed) {
		buffer = kmalloc(len, GFP_KERNEL);
		if (unlikely(!buffer))
			return -ENOMEM;

		/* TODO: this is very frequent pattern, make it a separate
		 * routine */
		err = jffs2_flash_read(c, ofs, len, &retlen, buffer);
		if (err) {
			JFFS2_ERROR("can not read %d bytes from 0x%08x, error code: %d.\n", len, ofs, err);
			goto free_out;
		}

		if (retlen != len) {
			JFFS2_ERROR("short read at %#08x: %zd instead of %d.\n", ofs, retlen, len);
			err = -EIO;
			goto free_out;
		}
	}

	/* Continue calculating CRC */
	crc = crc32(tn->partial_crc, buffer, len);
	if(!pointed)
		kfree(buffer);
#ifndef __ECOS
	else
		mtd_unpoint(c->mtd, ofs, len);
#endif

	if (crc != tn->data_crc) {
		JFFS2_NOTICE("wrong data CRC in data node at 0x%08x: read %#08x, calculated %#08x.\n",
			     ref_offset(ref), tn->data_crc, crc);
		return 1;
	}

adj_acc:
	jeb = &c->blocks[ref->flash_offset / c->sector_size];
	len = ref_totlen(c, jeb, ref);
	/* If it should be REF_NORMAL, it'll get marked as such when
	   we build the fragtree, shortly. No need to worry about GC
	   moving it while it's marked REF_PRISTINE -- GC won't happen
	   till we've finished checking every inode anyway. */
	ref->flash_offset |= REF_PRISTINE;
	/*
	 * Mark the node as having been checked and fix the
	 * accounting accordingly.
	 */
	spin_lock(&c->erase_completion_lock);
	jeb->used_size += len;
	jeb->unchecked_size -= len;
	c->used_size += len;
	c->unchecked_size -= len;
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);
	spin_unlock(&c->erase_completion_lock);

	return 0;

free_out:
	if(!pointed)
		kfree(buffer);
#ifndef __ECOS
	else
		mtd_unpoint(c->mtd, ofs, len);
#endif
	return err;
}
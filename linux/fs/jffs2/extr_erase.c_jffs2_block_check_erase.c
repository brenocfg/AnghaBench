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
typedef  size_t uint32_t ;
struct jffs2_sb_info {size_t sector_size; int /*<<< orphan*/  mtd; } ;
struct jffs2_eraseblock {size_t offset; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*,size_t) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t min (size_t,size_t) ; 
 int mtd_point (int /*<<< orphan*/ ,size_t,size_t,size_t*,void**,int /*<<< orphan*/ *) ; 
 int mtd_read (int /*<<< orphan*/ ,size_t,size_t,size_t*,void*) ; 
 int /*<<< orphan*/  mtd_unpoint (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long,...) ; 

__attribute__((used)) static int jffs2_block_check_erase(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb, uint32_t *bad_offset)
{
	void *ebuf;
	uint32_t ofs;
	size_t retlen;
	int ret;
	unsigned long *wordebuf;

	ret = mtd_point(c->mtd, jeb->offset, c->sector_size, &retlen,
			&ebuf, NULL);
	if (ret != -EOPNOTSUPP) {
		if (ret) {
			jffs2_dbg(1, "MTD point failed %d\n", ret);
			goto do_flash_read;
		}
		if (retlen < c->sector_size) {
			/* Don't muck about if it won't let us point to the whole erase sector */
			jffs2_dbg(1, "MTD point returned len too short: 0x%zx\n",
				  retlen);
			mtd_unpoint(c->mtd, jeb->offset, retlen);
			goto do_flash_read;
		}
		wordebuf = ebuf-sizeof(*wordebuf);
		retlen /= sizeof(*wordebuf);
		do {
		   if (*++wordebuf != ~0)
			   break;
		} while(--retlen);
		mtd_unpoint(c->mtd, jeb->offset, c->sector_size);
		if (retlen) {
			pr_warn("Newly-erased block contained word 0x%lx at offset 0x%08tx\n",
				*wordebuf,
				jeb->offset +
				c->sector_size-retlen * sizeof(*wordebuf));
			return -EIO;
		}
		return 0;
	}
 do_flash_read:
	ebuf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!ebuf) {
		pr_warn("Failed to allocate page buffer for verifying erase at 0x%08x. Refiling\n",
			jeb->offset);
		return -EAGAIN;
	}

	jffs2_dbg(1, "Verifying erase at 0x%08x\n", jeb->offset);

	for (ofs = jeb->offset; ofs < jeb->offset + c->sector_size; ) {
		uint32_t readlen = min((uint32_t)PAGE_SIZE, jeb->offset + c->sector_size - ofs);
		int i;

		*bad_offset = ofs;

		ret = mtd_read(c->mtd, ofs, readlen, &retlen, ebuf);
		if (ret) {
			pr_warn("Read of newly-erased block at 0x%08x failed: %d. Putting on bad_list\n",
				ofs, ret);
			ret = -EIO;
			goto fail;
		}
		if (retlen != readlen) {
			pr_warn("Short read from newly-erased block at 0x%08x. Wanted %d, got %zd\n",
				ofs, readlen, retlen);
			ret = -EIO;
			goto fail;
		}
		for (i=0; i<readlen; i += sizeof(unsigned long)) {
			/* It's OK. We know it's properly aligned */
			unsigned long *datum = ebuf + i;
			if (*datum + 1) {
				*bad_offset += i;
				pr_warn("Newly-erased block contained word 0x%lx at offset 0x%08x\n",
					*datum, *bad_offset);
				ret = -EIO;
				goto fail;
			}
		}
		ofs += readlen;
		cond_resched();
	}
	ret = 0;
fail:
	kfree(ebuf);
	return ret;
}
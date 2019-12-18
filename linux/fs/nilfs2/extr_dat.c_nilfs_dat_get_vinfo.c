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
struct nilfs_vinfo {unsigned long vi_vblocknr; void* vi_blocknr; void* vi_end; void* vi_start; } ;
struct nilfs_dat_entry {int /*<<< orphan*/  de_blocknr; int /*<<< orphan*/  de_end; int /*<<< orphan*/  de_start; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  int ssize_t ;
typedef  unsigned long __u64 ;
struct TYPE_2__ {unsigned long mi_entries_per_block; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct nilfs_dat_entry* nilfs_palloc_block_get_entry (struct inode*,unsigned long,struct buffer_head*,void*) ; 
 int nilfs_palloc_get_entry_block (struct inode*,unsigned long,int /*<<< orphan*/ ,struct buffer_head**) ; 

ssize_t nilfs_dat_get_vinfo(struct inode *dat, void *buf, unsigned int visz,
			    size_t nvi)
{
	struct buffer_head *entry_bh;
	struct nilfs_dat_entry *entry;
	struct nilfs_vinfo *vinfo = buf;
	__u64 first, last;
	void *kaddr;
	unsigned long entries_per_block = NILFS_MDT(dat)->mi_entries_per_block;
	int i, j, n, ret;

	for (i = 0; i < nvi; i += n) {
		ret = nilfs_palloc_get_entry_block(dat, vinfo->vi_vblocknr,
						   0, &entry_bh);
		if (ret < 0)
			return ret;
		kaddr = kmap_atomic(entry_bh->b_page);
		/* last virtual block number in this block */
		first = vinfo->vi_vblocknr;
		do_div(first, entries_per_block);
		first *= entries_per_block;
		last = first + entries_per_block - 1;
		for (j = i, n = 0;
		     j < nvi && vinfo->vi_vblocknr >= first &&
			     vinfo->vi_vblocknr <= last;
		     j++, n++, vinfo = (void *)vinfo + visz) {
			entry = nilfs_palloc_block_get_entry(
				dat, vinfo->vi_vblocknr, entry_bh, kaddr);
			vinfo->vi_start = le64_to_cpu(entry->de_start);
			vinfo->vi_end = le64_to_cpu(entry->de_end);
			vinfo->vi_blocknr = le64_to_cpu(entry->de_blocknr);
		}
		kunmap_atomic(kaddr);
		brelse(entry_bh);
	}

	return nvi;
}
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
typedef  int /*<<< orphan*/  u64 ;
struct nilfs_segment_usage {scalar_t__ su_flags; scalar_t__ su_nblocks; int /*<<< orphan*/  su_lastmod; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int ncleansegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NILFS_SEGMENT_USAGE_DIRTY ; 
 TYPE_1__* NILFS_SUI (struct inode*) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int nilfs_segment_usage_clean (struct nilfs_segment_usage*) ; 
 int nilfs_segment_usage_dirty (struct nilfs_segment_usage*) ; 
 struct nilfs_segment_usage* nilfs_sufile_block_get_segment_usage (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,void*) ; 
 int /*<<< orphan*/  nilfs_sufile_mod_counter (struct buffer_head*,int /*<<< orphan*/ ,int) ; 

void nilfs_sufile_do_scrap(struct inode *sufile, __u64 segnum,
			   struct buffer_head *header_bh,
			   struct buffer_head *su_bh)
{
	struct nilfs_segment_usage *su;
	void *kaddr;
	int clean, dirty;

	kaddr = kmap_atomic(su_bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, su_bh, kaddr);
	if (su->su_flags == cpu_to_le32(BIT(NILFS_SEGMENT_USAGE_DIRTY)) &&
	    su->su_nblocks == cpu_to_le32(0)) {
		kunmap_atomic(kaddr);
		return;
	}
	clean = nilfs_segment_usage_clean(su);
	dirty = nilfs_segment_usage_dirty(su);

	/* make the segment garbage */
	su->su_lastmod = cpu_to_le64(0);
	su->su_nblocks = cpu_to_le32(0);
	su->su_flags = cpu_to_le32(BIT(NILFS_SEGMENT_USAGE_DIRTY));
	kunmap_atomic(kaddr);

	nilfs_sufile_mod_counter(header_bh, clean ? (u64)-1 : 0, dirty ? 0 : 1);
	NILFS_SUI(sufile)->ncleansegs -= clean;

	mark_buffer_dirty(su_bh);
	nilfs_mdt_mark_dirty(sufile);
}
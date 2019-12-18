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
struct gc_inode_list {int /*<<< orphan*/  iroot; int /*<<< orphan*/  ilist; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; int /*<<< orphan*/  gc_mutex; scalar_t__ segs_per_sec; } ;

/* Variables and functions */
 int CURSEG_HOT_DATA ; 
 int EAGAIN ; 
 int /*<<< orphan*/  FG_GC ; 
 int /*<<< orphan*/  FREE_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  LIST_HEAD_INIT (int /*<<< orphan*/ ) ; 
 int NR_CURSEG_TYPE ; 
 int /*<<< orphan*/  RADIX_TREE_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocate_segment_for_resize (struct f2fs_sb_info*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  do_garbage_collect (struct f2fs_sb_info*,unsigned int,struct gc_inode_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_err (struct f2fs_sb_info*,char*,unsigned int) ; 
 int f2fs_sync_fs (int /*<<< orphan*/ ,int) ; 
 unsigned int find_next_inuse (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ get_valid_blocks (struct f2fs_sb_info*,unsigned int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_gc_inode (struct gc_inode_list*) ; 

__attribute__((used)) static int free_segment_range(struct f2fs_sb_info *sbi, unsigned int start,
							unsigned int end)
{
	int type;
	unsigned int segno, next_inuse;
	int err = 0;

	/* Move out cursegs from the target range */
	for (type = CURSEG_HOT_DATA; type < NR_CURSEG_TYPE; type++)
		allocate_segment_for_resize(sbi, type, start, end);

	/* do GC to move out valid blocks in the range */
	for (segno = start; segno <= end; segno += sbi->segs_per_sec) {
		struct gc_inode_list gc_list = {
			.ilist = LIST_HEAD_INIT(gc_list.ilist),
			.iroot = RADIX_TREE_INIT(gc_list.iroot, GFP_NOFS),
		};

		mutex_lock(&sbi->gc_mutex);
		do_garbage_collect(sbi, segno, &gc_list, FG_GC);
		mutex_unlock(&sbi->gc_mutex);
		put_gc_inode(&gc_list);

		if (get_valid_blocks(sbi, segno, true))
			return -EAGAIN;
	}

	err = f2fs_sync_fs(sbi->sb, 1);
	if (err)
		return err;

	next_inuse = find_next_inuse(FREE_I(sbi), end + 1, start);
	if (next_inuse <= end) {
		f2fs_err(sbi, "segno %u should be free but still inuse!",
			 next_inuse);
		f2fs_bug_on(sbi, 1);
	}
	return err;
}
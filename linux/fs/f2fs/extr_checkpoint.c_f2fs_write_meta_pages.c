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
struct writeback_control {scalar_t__ sync_mode; long nr_to_write; int /*<<< orphan*/  pages_skipped; } ;
struct f2fs_sb_info {int /*<<< orphan*/  cp_mutex; } ;
struct address_space {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_DIRTY_META ; 
 struct f2fs_sb_info* F2FS_M_SB (struct address_space*) ; 
 int /*<<< orphan*/  FS_META_IO ; 
 int /*<<< orphan*/  META ; 
 int /*<<< orphan*/  SBI_POR_DOING ; 
 scalar_t__ WB_SYNC_ALL ; 
 long f2fs_sync_meta_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 scalar_t__ get_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 long max (long,long) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nr_pages_to_skip (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 long nr_pages_to_write (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct writeback_control*) ; 
 int /*<<< orphan*/  trace_f2fs_writepages (int /*<<< orphan*/ ,struct writeback_control*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_write_meta_pages(struct address_space *mapping,
				struct writeback_control *wbc)
{
	struct f2fs_sb_info *sbi = F2FS_M_SB(mapping);
	long diff, written;

	if (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		goto skip_write;

	/* collect a number of dirty meta pages and write together */
	if (wbc->sync_mode != WB_SYNC_ALL &&
			get_pages(sbi, F2FS_DIRTY_META) <
					nr_pages_to_skip(sbi, META))
		goto skip_write;

	/* if locked failed, cp will flush dirty pages instead */
	if (!mutex_trylock(&sbi->cp_mutex))
		goto skip_write;

	trace_f2fs_writepages(mapping->host, wbc, META);
	diff = nr_pages_to_write(sbi, META, wbc);
	written = f2fs_sync_meta_pages(sbi, META, wbc->nr_to_write, FS_META_IO);
	mutex_unlock(&sbi->cp_mutex);
	wbc->nr_to_write = max((long)0, wbc->nr_to_write - written - diff);
	return 0;

skip_write:
	wbc->pages_skipped += get_pages(sbi, F2FS_DIRTY_META);
	trace_f2fs_writepages(mapping->host, wbc, META);
	return 0;
}
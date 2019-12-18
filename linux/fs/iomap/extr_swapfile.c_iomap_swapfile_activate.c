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
struct swap_info_struct {scalar_t__ highest_bit; scalar_t__ pages; scalar_t__ max; } ;
struct TYPE_2__ {scalar_t__ length; } ;
struct iomap_swapfile_info {int nr_extents; scalar_t__ nr_pages; scalar_t__ lowest_ppage; scalar_t__ highest_ppage; TYPE_1__ iomap; struct swap_info_struct* sis; } ;
struct iomap_ops {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ sector_t ;
typedef  int loff_t ;

/* Variables and functions */
 int ALIGN_DOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMAP_REPORT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int iomap_apply (struct inode*,int,int,int /*<<< orphan*/ ,struct iomap_ops const*,struct iomap_swapfile_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomap_swapfile_activate_actor ; 
 int iomap_swapfile_add_extent (struct iomap_swapfile_info*) ; 
 int vfs_fsync (struct file*,int) ; 

int iomap_swapfile_activate(struct swap_info_struct *sis,
		struct file *swap_file, sector_t *pagespan,
		const struct iomap_ops *ops)
{
	struct iomap_swapfile_info isi = {
		.sis = sis,
		.lowest_ppage = (sector_t)-1ULL,
	};
	struct address_space *mapping = swap_file->f_mapping;
	struct inode *inode = mapping->host;
	loff_t pos = 0;
	loff_t len = ALIGN_DOWN(i_size_read(inode), PAGE_SIZE);
	loff_t ret;

	/*
	 * Persist all file mapping metadata so that we won't have any
	 * IOMAP_F_DIRTY iomaps.
	 */
	ret = vfs_fsync(swap_file, 1);
	if (ret)
		return ret;

	while (len > 0) {
		ret = iomap_apply(inode, pos, len, IOMAP_REPORT,
				ops, &isi, iomap_swapfile_activate_actor);
		if (ret <= 0)
			return ret;

		pos += ret;
		len -= ret;
	}

	if (isi.iomap.length) {
		ret = iomap_swapfile_add_extent(&isi);
		if (ret)
			return ret;
	}

	*pagespan = 1 + isi.highest_ppage - isi.lowest_ppage;
	sis->max = isi.nr_pages;
	sis->pages = isi.nr_pages - 1;
	sis->highest_bit = isi.nr_pages - 1;
	return isi.nr_extents;
}
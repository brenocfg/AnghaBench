#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct page {TYPE_2__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_io_geometry {int len; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_3__ {int bi_size; scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 unsigned long EXTENT_BIO_COMPRESSED ; 
 int btrfs_get_io_geometry (struct btrfs_fs_info*,int /*<<< orphan*/ ,int,int,struct btrfs_io_geometry*) ; 
 int /*<<< orphan*/  btrfs_op (struct bio*) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 

int btrfs_bio_fits_in_stripe(struct page *page, size_t size, struct bio *bio,
			     unsigned long bio_flags)
{
	struct inode *inode = page->mapping->host;
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	u64 logical = (u64)bio->bi_iter.bi_sector << 9;
	u64 length = 0;
	u64 map_length;
	int ret;
	struct btrfs_io_geometry geom;

	if (bio_flags & EXTENT_BIO_COMPRESSED)
		return 0;

	length = bio->bi_iter.bi_size;
	map_length = length;
	ret = btrfs_get_io_geometry(fs_info, btrfs_op(bio), logical, map_length,
				    &geom);
	if (ret < 0)
		return ret;

	if (geom.len < length + size)
		return 1;
	return 0;
}
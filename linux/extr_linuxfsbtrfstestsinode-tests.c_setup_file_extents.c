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
typedef  int u64 ;
typedef  int u32 ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_COMPRESS_ZLIB ; 
 int /*<<< orphan*/  BTRFS_FILE_EXTENT_INLINE ; 
 int /*<<< orphan*/  BTRFS_FILE_EXTENT_PREALLOC ; 
 int /*<<< orphan*/  BTRFS_FILE_EXTENT_REG ; 
 int SZ_1M ; 
 int /*<<< orphan*/  insert_extent (struct btrfs_root*,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_file_extents(struct btrfs_root *root, u32 sectorsize)
{
	int slot = 0;
	u64 disk_bytenr = SZ_1M;
	u64 offset = 0;

	/* First we want a hole */
	insert_extent(root, offset, 5, 5, 0, 0, 0, BTRFS_FILE_EXTENT_REG, 0,
		      slot);
	slot++;
	offset += 5;

	/*
	 * Now we want an inline extent, I don't think this is possible but hey
	 * why not?  Also keep in mind if we have an inline extent it counts as
	 * the whole first page.  If we were to expand it we would have to cow
	 * and we wouldn't have an inline extent anymore.
	 */
	insert_extent(root, offset, 1, 1, 0, 0, 0, BTRFS_FILE_EXTENT_INLINE, 0,
		      slot);
	slot++;
	offset = sectorsize;

	/* Now another hole */
	insert_extent(root, offset, 4, 4, 0, 0, 0, BTRFS_FILE_EXTENT_REG, 0,
		      slot);
	slot++;
	offset += 4;

	/* Now for a regular extent */
	insert_extent(root, offset, sectorsize - 1, sectorsize - 1, 0,
		      disk_bytenr, sectorsize, BTRFS_FILE_EXTENT_REG, 0, slot);
	slot++;
	disk_bytenr += sectorsize;
	offset += sectorsize - 1;

	/*
	 * Now for 3 extents that were split from a hole punch so we test
	 * offsets properly.
	 */
	insert_extent(root, offset, sectorsize, 4 * sectorsize, 0, disk_bytenr,
		      4 * sectorsize, BTRFS_FILE_EXTENT_REG, 0, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, sectorsize, sectorsize, 0, 0, 0,
		      BTRFS_FILE_EXTENT_REG, 0, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, 2 * sectorsize, 4 * sectorsize,
		      2 * sectorsize, disk_bytenr, 4 * sectorsize,
		      BTRFS_FILE_EXTENT_REG, 0, slot);
	slot++;
	offset += 2 * sectorsize;
	disk_bytenr += 4 * sectorsize;

	/* Now for a unwritten prealloc extent */
	insert_extent(root, offset, sectorsize, sectorsize, 0, disk_bytenr,
		sectorsize, BTRFS_FILE_EXTENT_PREALLOC, 0, slot);
	slot++;
	offset += sectorsize;

	/*
	 * We want to jack up disk_bytenr a little more so the em stuff doesn't
	 * merge our records.
	 */
	disk_bytenr += 2 * sectorsize;

	/*
	 * Now for a partially written prealloc extent, basically the same as
	 * the hole punch example above.  Ram_bytes never changes when you mark
	 * extents written btw.
	 */
	insert_extent(root, offset, sectorsize, 4 * sectorsize, 0, disk_bytenr,
		      4 * sectorsize, BTRFS_FILE_EXTENT_PREALLOC, 0, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, sectorsize, 4 * sectorsize, sectorsize,
		      disk_bytenr, 4 * sectorsize, BTRFS_FILE_EXTENT_REG, 0,
		      slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, 2 * sectorsize, 4 * sectorsize,
		      2 * sectorsize, disk_bytenr, 4 * sectorsize,
		      BTRFS_FILE_EXTENT_PREALLOC, 0, slot);
	slot++;
	offset += 2 * sectorsize;
	disk_bytenr += 4 * sectorsize;

	/* Now a normal compressed extent */
	insert_extent(root, offset, 2 * sectorsize, 2 * sectorsize, 0,
		      disk_bytenr, sectorsize, BTRFS_FILE_EXTENT_REG,
		      BTRFS_COMPRESS_ZLIB, slot);
	slot++;
	offset += 2 * sectorsize;
	/* No merges */
	disk_bytenr += 2 * sectorsize;

	/* Now a split compressed extent */
	insert_extent(root, offset, sectorsize, 4 * sectorsize, 0, disk_bytenr,
		      sectorsize, BTRFS_FILE_EXTENT_REG,
		      BTRFS_COMPRESS_ZLIB, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, sectorsize, sectorsize, 0,
		      disk_bytenr + sectorsize, sectorsize,
		      BTRFS_FILE_EXTENT_REG, 0, slot);
	slot++;
	offset += sectorsize;
	insert_extent(root, offset, 2 * sectorsize, 4 * sectorsize,
		      2 * sectorsize, disk_bytenr, sectorsize,
		      BTRFS_FILE_EXTENT_REG, BTRFS_COMPRESS_ZLIB, slot);
	slot++;
	offset += 2 * sectorsize;
	disk_bytenr += 2 * sectorsize;

	/* Now extents that have a hole but no hole extent */
	insert_extent(root, offset, sectorsize, sectorsize, 0, disk_bytenr,
		      sectorsize, BTRFS_FILE_EXTENT_REG, 0, slot);
	slot++;
	offset += 4 * sectorsize;
	disk_bytenr += sectorsize;
	insert_extent(root, offset, sectorsize, sectorsize, 0, disk_bytenr,
		      sectorsize, BTRFS_FILE_EXTENT_REG, 0, slot);
}
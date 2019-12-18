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
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int BTRFS_MAX_METADATA_BLOCKSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TEST_ALLOC_FS_INFO ; 
 int /*<<< orphan*/  TEST_ALLOC_ROOT ; 
 struct extent_buffer* __alloc_dummy_extent_buffer (struct btrfs_fs_info*,int,unsigned long) ; 
 int __test_eb_bitmaps (unsigned long*,struct extent_buffer*,unsigned long) ; 
 struct btrfs_fs_info* btrfs_alloc_dummy_fs_info (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  btrfs_free_dummy_fs_info (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 unsigned long* kmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_err (char*) ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_eb_bitmaps(u32 sectorsize, u32 nodesize)
{
	struct btrfs_fs_info *fs_info;
	unsigned long len;
	unsigned long *bitmap = NULL;
	struct extent_buffer *eb = NULL;
	int ret;

	test_msg("running extent buffer bitmap tests");

	/*
	 * In ppc64, sectorsize can be 64K, thus 4 * 64K will be larger than
	 * BTRFS_MAX_METADATA_BLOCKSIZE.
	 */
	len = (sectorsize < BTRFS_MAX_METADATA_BLOCKSIZE)
		? sectorsize * 4 : sectorsize;

	fs_info = btrfs_alloc_dummy_fs_info(len, len);
	if (!fs_info) {
		test_std_err(TEST_ALLOC_FS_INFO);
		return -ENOMEM;
	}

	bitmap = kmalloc(len, GFP_KERNEL);
	if (!bitmap) {
		test_err("couldn't allocate test bitmap");
		ret = -ENOMEM;
		goto out;
	}

	eb = __alloc_dummy_extent_buffer(fs_info, 0, len);
	if (!eb) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = -ENOMEM;
		goto out;
	}

	ret = __test_eb_bitmaps(bitmap, eb, len);
	if (ret)
		goto out;

	/* Do it over again with an extent buffer which isn't page-aligned. */
	free_extent_buffer(eb);
	eb = __alloc_dummy_extent_buffer(fs_info, nodesize / 2, len);
	if (!eb) {
		test_std_err(TEST_ALLOC_ROOT);
		ret = -ENOMEM;
		goto out;
	}

	ret = __test_eb_bitmaps(bitmap, eb, len);
out:
	free_extent_buffer(eb);
	kfree(bitmap);
	btrfs_free_dummy_fs_info(fs_info);
	return ret;
}
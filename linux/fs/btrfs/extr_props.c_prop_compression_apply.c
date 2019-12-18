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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {int prop_compress; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BTRFS_COMPRESS_LZO ; 
 int BTRFS_COMPRESS_NONE ; 
 int BTRFS_COMPRESS_ZLIB ; 
 int BTRFS_COMPRESS_ZSTD ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_COMPRESS ; 
 int /*<<< orphan*/  BTRFS_INODE_NOCOMPRESS ; 
 int /*<<< orphan*/  COMPRESS_LZO ; 
 int /*<<< orphan*/  COMPRESS_ZSTD ; 
 int EINVAL ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_fs_incompat (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static int prop_compression_apply(struct inode *inode, const char *value,
				  size_t len)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	int type;

	if (len == 0) {
		BTRFS_I(inode)->flags |= BTRFS_INODE_NOCOMPRESS;
		BTRFS_I(inode)->flags &= ~BTRFS_INODE_COMPRESS;
		BTRFS_I(inode)->prop_compress = BTRFS_COMPRESS_NONE;

		return 0;
	}

	if (!strncmp("lzo", value, 3)) {
		type = BTRFS_COMPRESS_LZO;
		btrfs_set_fs_incompat(fs_info, COMPRESS_LZO);
	} else if (!strncmp("zlib", value, 4)) {
		type = BTRFS_COMPRESS_ZLIB;
	} else if (!strncmp("zstd", value, 4)) {
		type = BTRFS_COMPRESS_ZSTD;
		btrfs_set_fs_incompat(fs_info, COMPRESS_ZSTD);
	} else {
		return -EINVAL;
	}

	BTRFS_I(inode)->flags &= ~BTRFS_INODE_NOCOMPRESS;
	BTRFS_I(inode)->flags |= BTRFS_INODE_COMPRESS;
	BTRFS_I(inode)->prop_compress = type;

	return 0;
}
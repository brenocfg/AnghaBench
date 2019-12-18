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
typedef  int loff_t ;

/* Variables and functions */
 int EXT3_NDIR_BLOCKS ; 
 int MAX_LFS_FILESIZE ; 

loff_t ext3_max_bitmap_size(int bits, int has_huge_files)
{
    loff_t res = EXT3_NDIR_BLOCKS;
    int meta_blocks;
    loff_t upper_limit;
    /* This is calculated to be the largest file size for a
     * dense, bitmapped file such that the total number of
     * sectors in the file, including data and all indirect blocks,
     * does not exceed 2^48 -1
     * __u32 i_blocks_lo and _u16 i_blocks_high representing the
     * total number of  512 bytes blocks of the file
     */

    if (!has_huge_files) {
        /*
         * !has_huge_files or CONFIG_LBD is not enabled
         * implies the inode i_block represent total blocks in
         * 512 bytes 32 == size of vfs inode i_blocks * 8
         */
        upper_limit = ((loff_t)1 << 32) - 1;

        /* total blocks in file system block size */
        upper_limit >>= (bits - 9);

    } else {
        /*
         * We use 48 bit ext4_inode i_blocks
         * With EXT4_HUGE_FILE_FL set the i_blocks
         * represent total number of blocks in
         * file system block size
         */
        upper_limit = ((loff_t)1 << 48) - 1;

    }

    /* indirect blocks */
    meta_blocks = 1;
    /* double indirect blocks */
    meta_blocks += 1 + ((loff_t)1 << (bits-2));
    /* tripple indirect blocks */
    meta_blocks += 1 + ((loff_t)1 << (bits-2)) + ((loff_t)1 << (2*(bits-2)));

    upper_limit -= meta_blocks;
    upper_limit <<= bits;

    res += (loff_t)1 << (bits-2);
    res += (loff_t)1 << (2*(bits-2));
    res += (loff_t)1 << (3*(bits-2));
    res <<= bits;
    if (res > upper_limit)
        res = upper_limit;

    if (res > MAX_LFS_FILESIZE)
        res = MAX_LFS_FILESIZE;

    return res;
}
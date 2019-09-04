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
typedef  long long loff_t ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned int,unsigned int) ; 
 long long EXT2_NDIR_BLOCKS ; 
 long long MAX_LFS_FILESIZE ; 

__attribute__((used)) static loff_t ext2_max_size(int bits)
{
	loff_t res = EXT2_NDIR_BLOCKS;
	int meta_blocks;
	unsigned int upper_limit;
	unsigned int ppb = 1 << (bits-2);

	/* This is calculated to be the largest file size for a
	 * dense, file such that the total number of
	 * sectors in the file, including data and all indirect blocks,
	 * does not exceed 2^32 -1
	 * __u32 i_blocks representing the total number of
	 * 512 bytes blocks of the file
	 */
	upper_limit = (1LL << 32) - 1;

	/* total blocks in file system block size */
	upper_limit >>= (bits - 9);

	/* Compute how many blocks we can address by block tree */
	res += 1LL << (bits-2);
	res += 1LL << (2*(bits-2));
	res += 1LL << (3*(bits-2));
	/* Does block tree limit file size? */
	if (res < upper_limit)
		goto check_lfs;

	res = upper_limit;
	/* How many metadata blocks are needed for addressing upper_limit? */
	upper_limit -= EXT2_NDIR_BLOCKS;
	/* indirect blocks */
	meta_blocks = 1;
	upper_limit -= ppb;
	/* double indirect blocks */
	if (upper_limit < ppb * ppb) {
		meta_blocks += 1 + DIV_ROUND_UP(upper_limit, ppb);
		res -= meta_blocks;
		goto check_lfs;
	}
	meta_blocks += 1 + ppb;
	upper_limit -= ppb * ppb;
	/* tripple indirect blocks for the rest */
	meta_blocks += 1 + DIV_ROUND_UP(upper_limit, ppb) +
		DIV_ROUND_UP(upper_limit, ppb*ppb);
	res -= meta_blocks;
check_lfs:
	res <<= bits;
	if (res > MAX_LFS_FILESIZE)
		res = MAX_LFS_FILESIZE;

	return res;
}
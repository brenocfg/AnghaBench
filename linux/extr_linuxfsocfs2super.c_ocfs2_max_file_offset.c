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

/* Variables and functions */

__attribute__((used)) static unsigned long long ocfs2_max_file_offset(unsigned int bbits,
						unsigned int cbits)
{
	unsigned int bytes = 1 << cbits;
	unsigned int trim = bytes;
	unsigned int bitshift = 32;

	/*
	 * i_size and all block offsets in ocfs2 are always 64 bits
	 * wide. i_clusters is 32 bits, in cluster-sized units. So on
	 * 64 bit platforms, cluster size will be the limiting factor.
	 */

#if BITS_PER_LONG == 32
# if defined(CONFIG_LBDAF)
	BUILD_BUG_ON(sizeof(sector_t) != 8);
	/*
	 * We might be limited by page cache size.
	 */
	if (bytes > PAGE_SIZE) {
		bytes = PAGE_SIZE;
		trim = 1;
		/*
		 * Shift by 31 here so that we don't get larger than
		 * MAX_LFS_FILESIZE
		 */
		bitshift = 31;
	}
# else
	/*
	 * We are limited by the size of sector_t. Use block size, as
	 * that's what we expose to the VFS.
	 */
	bytes = 1 << bbits;
	trim = 1;
	bitshift = 31;
# endif
#endif

	/*
	 * Trim by a whole cluster when we can actually approach the
	 * on-disk limits. Otherwise we can overflow i_clusters when
	 * an extent start is at the max offset.
	 */
	return (((unsigned long long)bytes) << bitshift) - trim;
}
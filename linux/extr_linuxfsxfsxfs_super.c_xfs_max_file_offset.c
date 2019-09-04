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
typedef  unsigned int uint64_t ;

/* Variables and functions */
 int BITS_PER_LONG ; 

__attribute__((used)) static uint64_t
xfs_max_file_offset(
	unsigned int		blockshift)
{
	unsigned int		pagefactor = 1;
	unsigned int		bitshift = BITS_PER_LONG - 1;

	/* Figure out maximum filesize, on Linux this can depend on
	 * the filesystem blocksize (on 32 bit platforms).
	 * __block_write_begin does this in an [unsigned] long...
	 *      page->index << (PAGE_SHIFT - bbits)
	 * So, for page sized blocks (4K on 32 bit platforms),
	 * this wraps at around 8Tb (hence MAX_LFS_FILESIZE which is
	 *      (((u64)PAGE_SIZE << (BITS_PER_LONG-1))-1)
	 * but for smaller blocksizes it is less (bbits = log2 bsize).
	 * Note1: get_block_t takes a long (implicit cast from above)
	 * Note2: The Large Block Device (LBD and HAVE_SECTOR_T) patch
	 * can optionally convert the [unsigned] long from above into
	 * an [unsigned] long long.
	 */

#if BITS_PER_LONG == 32
# if defined(CONFIG_LBDAF)
	ASSERT(sizeof(sector_t) == 8);
	pagefactor = PAGE_SIZE;
	bitshift = BITS_PER_LONG;
# else
	pagefactor = PAGE_SIZE >> (PAGE_SHIFT - blockshift);
# endif
#endif

	return (((uint64_t)pagefactor) << bitshift) - 1;
}
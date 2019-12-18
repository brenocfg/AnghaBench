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
typedef  long long u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  size ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int,int,long long,int,long long) ; 
 int fill_meta_index (struct inode*,int,long long*,int*,long long*) ; 
 long long read_indexes (int /*<<< orphan*/ ,int,long long*,int*) ; 
 int squashfs_block_size (int /*<<< orphan*/ ) ; 
 int squashfs_read_metadata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long long*,int*,int) ; 

__attribute__((used)) static int read_blocklist(struct inode *inode, int index, u64 *block)
{
	u64 start;
	long long blks;
	int offset;
	__le32 size;
	int res = fill_meta_index(inode, index, &start, &offset, block);

	TRACE("read_blocklist: res %d, index %d, start 0x%llx, offset"
		       " 0x%x, block 0x%llx\n", res, index, start, offset,
			*block);

	if (res < 0)
		return res;

	/*
	 * res contains the index of the mapping returned by fill_meta_index(),
	 * this will likely be less than the desired index (because the
	 * meta_index cache works at a higher granularity).  Read any
	 * extra block indexes needed.
	 */
	if (res < index) {
		blks = read_indexes(inode->i_sb, index - res, &start, &offset);
		if (blks < 0)
			return (int) blks;
		*block += blks;
	}

	/*
	 * Read length of block specified by index.
	 */
	res = squashfs_read_metadata(inode->i_sb, &size, &start, &offset,
			sizeof(size));
	if (res < 0)
		return res;
	return squashfs_block_size(size);
}
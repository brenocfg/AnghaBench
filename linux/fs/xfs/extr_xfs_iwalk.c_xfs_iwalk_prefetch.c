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
 unsigned int IWALK_MAX_INODE_PREFETCH ; 
 int XFS_INODES_PER_CHUNK ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int round_up (unsigned int,int) ; 

__attribute__((used)) static inline unsigned int
xfs_iwalk_prefetch(
	unsigned int		inodes)
{
	unsigned int		inobt_records;

	/*
	 * If the caller didn't tell us the number of inodes they wanted,
	 * assume the maximum prefetch possible for best performance.
	 * Otherwise, cap prefetch at that maximum so that we don't start an
	 * absurd amount of prefetch.
	 */
	if (inodes == 0)
		inodes = IWALK_MAX_INODE_PREFETCH;
	inodes = min(inodes, IWALK_MAX_INODE_PREFETCH);

	/* Round the inode count up to a full chunk. */
	inodes = round_up(inodes, XFS_INODES_PER_CHUNK);

	/*
	 * In order to convert the number of inodes to prefetch into an
	 * estimate of the number of inobt records to cache, we require a
	 * conversion factor that reflects our expectations of the average
	 * loading factor of an inode chunk.  Based on data gathered, most
	 * (but not all) filesystems manage to keep the inode chunks totally
	 * full, so we'll underestimate slightly so that our readahead will
	 * still deliver the performance we want on aging filesystems:
	 *
	 * inobt = inodes / (INODES_PER_CHUNK * (4 / 5));
	 *
	 * The funny math is to avoid integer division.
	 */
	inobt_records = (inodes * 5) / (4 * XFS_INODES_PER_CHUNK);

	/*
	 * Allocate enough space to prefetch at least two inobt records so that
	 * we can cache both the record where the iwalk started and the next
	 * record.  This simplifies the AG inode walk loop setup code.
	 */
	return max(inobt_records, 2U);
}
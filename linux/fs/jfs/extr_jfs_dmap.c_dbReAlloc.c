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
struct inode {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int ENOSPC ; 
 int dbAlloc (struct inode*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int dbExtend (struct inode*,scalar_t__,scalar_t__,scalar_t__) ; 

int
dbReAlloc(struct inode *ip,
	  s64 blkno, s64 nblocks, s64 addnblocks, s64 * results)
{
	int rc;

	/* try to extend the allocation in place.
	 */
	if ((rc = dbExtend(ip, blkno, nblocks, addnblocks)) == 0) {
		*results = blkno;
		return (0);
	} else {
		if (rc != -ENOSPC)
			return (rc);
	}

	/* could not extend the allocation in place, so allocate a
	 * new set of blocks for the entire request (i.e. try to get
	 * a range of contiguous blocks large enough to cover the
	 * existing allocation plus the additional blocks.)
	 */
	return (dbAlloc
		(ip, blkno + nblocks - 1, addnblocks + nblocks, results));
}
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
typedef  int /*<<< orphan*/  xad_t ;
struct inode {int i_blkbits; int i_size; TYPE_1__* i_sb; } ;
struct buffer_head {int b_size; } ;
typedef  int sector_t ;
typedef  int s64 ;
typedef  int s32 ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IREAD_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (struct inode*) ; 
 int /*<<< orphan*/  IWRITE_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWRITE_UNLOCK (struct inode*) ; 
 int /*<<< orphan*/  RDWRLOCK_NORMAL ; 
 int XAD_NOTRECORDED ; 
 int /*<<< orphan*/  XADaddress (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XADlength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XADoffset (int /*<<< orphan*/ *,int) ; 
 int addressXAD (int /*<<< orphan*/ *) ; 
 int extAlloc (struct inode*,int,int,int /*<<< orphan*/ *,int) ; 
 int extHint (struct inode*,int,int /*<<< orphan*/ *) ; 
 int extRecord (struct inode*,int /*<<< orphan*/ *) ; 
 int lengthXAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  xtLookup (struct inode*,int,int,int*,int*,int*,int /*<<< orphan*/ ) ; 

int jfs_get_block(struct inode *ip, sector_t lblock,
		  struct buffer_head *bh_result, int create)
{
	s64 lblock64 = lblock;
	int rc = 0;
	xad_t xad;
	s64 xaddr;
	int xflag;
	s32 xlen = bh_result->b_size >> ip->i_blkbits;

	/*
	 * Take appropriate lock on inode
	 */
	if (create)
		IWRITE_LOCK(ip, RDWRLOCK_NORMAL);
	else
		IREAD_LOCK(ip, RDWRLOCK_NORMAL);

	if (((lblock64 << ip->i_sb->s_blocksize_bits) < ip->i_size) &&
	    (!xtLookup(ip, lblock64, xlen, &xflag, &xaddr, &xlen, 0)) &&
	    xaddr) {
		if (xflag & XAD_NOTRECORDED) {
			if (!create)
				/*
				 * Allocated but not recorded, read treats
				 * this as a hole
				 */
				goto unlock;
#ifdef _JFS_4K
			XADoffset(&xad, lblock64);
			XADlength(&xad, xlen);
			XADaddress(&xad, xaddr);
#else				/* _JFS_4K */
			/*
			 * As long as block size = 4K, this isn't a problem.
			 * We should mark the whole page not ABNR, but how
			 * will we know to mark the other blocks BH_New?
			 */
			BUG();
#endif				/* _JFS_4K */
			rc = extRecord(ip, &xad);
			if (rc)
				goto unlock;
			set_buffer_new(bh_result);
		}

		map_bh(bh_result, ip->i_sb, xaddr);
		bh_result->b_size = xlen << ip->i_blkbits;
		goto unlock;
	}
	if (!create)
		goto unlock;

	/*
	 * Allocate a new block
	 */
#ifdef _JFS_4K
	if ((rc = extHint(ip, lblock64 << ip->i_sb->s_blocksize_bits, &xad)))
		goto unlock;
	rc = extAlloc(ip, xlen, lblock64, &xad, false);
	if (rc)
		goto unlock;

	set_buffer_new(bh_result);
	map_bh(bh_result, ip->i_sb, addressXAD(&xad));
	bh_result->b_size = lengthXAD(&xad) << ip->i_blkbits;

#else				/* _JFS_4K */
	/*
	 * We need to do whatever it takes to keep all but the last buffers
	 * in 4K pages - see jfs_write.c
	 */
	BUG();
#endif				/* _JFS_4K */

      unlock:
	/*
	 * Release lock on inode
	 */
	if (create)
		IWRITE_UNLOCK(ip);
	else
		IREAD_UNLOCK(ip);
	return rc;
}
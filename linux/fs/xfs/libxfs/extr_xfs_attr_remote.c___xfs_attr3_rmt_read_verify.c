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
typedef  int /*<<< orphan*/  xfs_failaddr_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb; TYPE_1__* m_attr_geo; } ;
struct xfs_buf {char* b_addr; int /*<<< orphan*/  b_length; int /*<<< orphan*/  b_bn; struct xfs_mount* b_mount; } ;
struct TYPE_2__ {int blksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BBTOB (int /*<<< orphan*/ ) ; 
 scalar_t__ BTOBB (int) ; 
 int EFSBADCRC ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_ATTR3_RMT_CRC_OFF ; 
 int /*<<< orphan*/  __this_address ; 
 int /*<<< orphan*/  xfs_attr3_rmt_verify (struct xfs_mount*,struct xfs_buf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_verify_cksum (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__xfs_attr3_rmt_read_verify(
	struct xfs_buf	*bp,
	bool		check_crc,
	xfs_failaddr_t	*failaddr)
{
	struct xfs_mount *mp = bp->b_mount;
	char		*ptr;
	int		len;
	xfs_daddr_t	bno;
	int		blksize = mp->m_attr_geo->blksize;

	/* no verification of non-crc buffers */
	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return 0;

	ptr = bp->b_addr;
	bno = bp->b_bn;
	len = BBTOB(bp->b_length);
	ASSERT(len >= blksize);

	while (len > 0) {
		if (check_crc &&
		    !xfs_verify_cksum(ptr, blksize, XFS_ATTR3_RMT_CRC_OFF)) {
			*failaddr = __this_address;
			return -EFSBADCRC;
		}
		*failaddr = xfs_attr3_rmt_verify(mp, bp, ptr, blksize, bno);
		if (*failaddr)
			return -EFSCORRUPTED;
		len -= blksize;
		ptr += blksize;
		bno += BTOBB(blksize);
	}

	if (len != 0) {
		*failaddr = __this_address;
		return -EFSCORRUPTED;
	}

	return 0;
}
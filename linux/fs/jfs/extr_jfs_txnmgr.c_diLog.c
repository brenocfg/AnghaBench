#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tlock {int type; int /*<<< orphan*/  flag; int /*<<< orphan*/  lock; struct metapage* mp; } ;
struct tblock {TYPE_2__* sb; } ;
struct pxd_lock {scalar_t__ index; int flag; int /*<<< orphan*/  pxd; } ;
struct metapage {int logical_size; int /*<<< orphan*/  index; } ;
struct TYPE_9__ {int /*<<< orphan*/  pxd; void* nxd; void* type; } ;
struct TYPE_8__ {void* inoext_idx; void* iagnum; } ;
struct TYPE_6__ {int /*<<< orphan*/  pxd; void* l2linesize; void* type; } ;
struct TYPE_10__ {TYPE_4__ updatemap; TYPE_3__ noredoinoext; TYPE_1__ redopage; } ;
struct lrd {void* backchain; TYPE_5__ log; void* type; } ;
struct jfs_log {int dummy; } ;
struct commit {scalar_t__* iplist; } ;
typedef  int /*<<< orphan*/  pxd_t ;
struct TYPE_7__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int L2INODESLOTSIZE ; 
 int LOG_ALLOCPXD ; 
 int LOG_FREEPXD ; 
 int LOG_INODE ; 
 int LOG_NOREDOINOEXT ; 
 int LOG_REDOPAGE ; 
 int LOG_UPDATEMAP ; 
 int /*<<< orphan*/  PXDaddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PXDlength (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ i ; 
 int /*<<< orphan*/  jfs_err (char*,struct tlock*) ; 
 int /*<<< orphan*/  lmLog (struct jfs_log*,struct tblock*,struct lrd*,struct tlock*) ; 
 int mlckALLOCPXD ; 
 scalar_t__ nlock ; 
 int tlckEA ; 
 int tlckENTRY ; 
 int tlckFREE ; 
 int /*<<< orphan*/  tlckUPDATEMAP ; 
 int /*<<< orphan*/  tlckWRITEPAGE ; 

__attribute__((used)) static int diLog(struct jfs_log * log, struct tblock * tblk, struct lrd * lrd,
		 struct tlock * tlck, struct commit * cd)
{
	int rc = 0;
	struct metapage *mp;
	pxd_t *pxd;
	struct pxd_lock *pxdlock;

	mp = tlck->mp;

	/* initialize as REDOPAGE record format */
	lrd->log.redopage.type = cpu_to_le16(LOG_INODE);
	lrd->log.redopage.l2linesize = cpu_to_le16(L2INODESLOTSIZE);

	pxd = &lrd->log.redopage.pxd;

	/*
	 *	inode after image
	 */
	if (tlck->type & tlckENTRY) {
		/* log after-image for logredo(): */
		lrd->type = cpu_to_le16(LOG_REDOPAGE);
		PXDaddress(pxd, mp->index);
		PXDlength(pxd,
			  mp->logical_size >> tblk->sb->s_blocksize_bits);
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, tlck));

		/* mark page as homeward bound */
		tlck->flag |= tlckWRITEPAGE;
	} else if (tlck->type & tlckFREE) {
		/*
		 *	free inode extent
		 *
		 * (pages of the freed inode extent have been invalidated and
		 * a maplock for free of the extent has been formatted at
		 * txLock() time);
		 *
		 * the tlock had been acquired on the inode allocation map page
		 * (iag) that specifies the freed extent, even though the map
		 * page is not itself logged, to prevent pageout of the map
		 * page before the log;
		 */

		/* log LOG_NOREDOINOEXT of the freed inode extent for
		 * logredo() to start NoRedoPage filters, and to update
		 * imap and bmap for free of the extent;
		 */
		lrd->type = cpu_to_le16(LOG_NOREDOINOEXT);
		/*
		 * For the LOG_NOREDOINOEXT record, we need
		 * to pass the IAG number and inode extent
		 * index (within that IAG) from which the
		 * the extent being released.  These have been
		 * passed to us in the iplist[1] and iplist[2].
		 */
		lrd->log.noredoinoext.iagnum =
		    cpu_to_le32((u32) (size_t) cd->iplist[1]);
		lrd->log.noredoinoext.inoext_idx =
		    cpu_to_le32((u32) (size_t) cd->iplist[2]);

		pxdlock = (struct pxd_lock *) & tlck->lock;
		*pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, NULL));

		/* update bmap */
		tlck->flag |= tlckUPDATEMAP;

		/* mark page as homeward bound */
		tlck->flag |= tlckWRITEPAGE;
	} else
		jfs_err("diLog: UFO type tlck:0x%p", tlck);
#ifdef  _JFS_WIP
	/*
	 *	alloc/free external EA extent
	 *
	 * a maplock for txUpdateMap() to update bPWMAP for alloc/free
	 * of the extent has been formatted at txLock() time;
	 */
	else {
		assert(tlck->type & tlckEA);

		/* log LOG_UPDATEMAP for logredo() to update bmap for
		 * alloc of new (and free of old) external EA extent;
		 */
		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		pxdlock = (struct pxd_lock *) & tlck->lock;
		nlock = pxdlock->index;
		for (i = 0; i < nlock; i++, pxdlock++) {
			if (pxdlock->flag & mlckALLOCPXD)
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_ALLOCPXD);
			else
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_FREEPXD);
			lrd->log.updatemap.nxd = cpu_to_le16(1);
			lrd->log.updatemap.pxd = pxdlock->pxd;
			lrd->backchain =
			    cpu_to_le32(lmLog(log, tblk, lrd, NULL));
		}

		/* update bmap */
		tlck->flag |= tlckUPDATEMAP;
	}
#endif				/* _JFS_WIP */

	return rc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct metapage {scalar_t__ data; } ;
struct inomap {int /*<<< orphan*/  im_numfree; TYPE_2__* im_agctl; TYPE_1__* im_ipimap; } ;
struct iag {int /*<<< orphan*/  nfreeinos; int /*<<< orphan*/  inofreeback; int /*<<< orphan*/  inofreefwd; int /*<<< orphan*/ * inosmap; int /*<<< orphan*/ * wmap; int /*<<< orphan*/ * inoext; int /*<<< orphan*/ * pmap; int /*<<< orphan*/  agstart; } ;
struct TYPE_4__ {int inofree; int numfree; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int BLKTOAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int EXTSPERSUM ; 
 int HIGHORDER ; 
 int INOSPEREXT ; 
 int /*<<< orphan*/  JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2EXTSPERSUM ; 
 int L2INOSPEREXT ; 
 int ONES ; 
 scalar_t__ addressPXD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int diIAGRead (struct inomap*,int,struct metapage**) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

__attribute__((used)) static int diAllocBit(struct inomap * imap, struct iag * iagp, int ino)
{
	int extno, bitno, agno, sword, rc;
	struct metapage *amp = NULL, *bmp = NULL;
	struct iag *aiagp = NULL, *biagp = NULL;
	u32 mask;

	/* check if this is the last free inode within the iag.
	 * if so, it will have to be removed from the ag free
	 * inode list, so get the iags preceding and following
	 * it on the list.
	 */
	if (iagp->nfreeinos == cpu_to_le32(1)) {
		if ((int) le32_to_cpu(iagp->inofreefwd) >= 0) {
			if ((rc =
			     diIAGRead(imap, le32_to_cpu(iagp->inofreefwd),
				       &amp)))
				return (rc);
			aiagp = (struct iag *) amp->data;
		}

		if ((int) le32_to_cpu(iagp->inofreeback) >= 0) {
			if ((rc =
			     diIAGRead(imap,
				       le32_to_cpu(iagp->inofreeback),
				       &bmp))) {
				if (amp)
					release_metapage(amp);
				return (rc);
			}
			biagp = (struct iag *) bmp->data;
		}
	}

	/* get the ag number, extent number, inode number within
	 * the extent.
	 */
	agno = BLKTOAG(le64_to_cpu(iagp->agstart), JFS_SBI(imap->im_ipimap->i_sb));
	extno = ino >> L2INOSPEREXT;
	bitno = ino & (INOSPEREXT - 1);

	/* compute the mask for setting the map.
	 */
	mask = HIGHORDER >> bitno;

	/* the inode should be free and backed.
	 */
	if (((le32_to_cpu(iagp->pmap[extno]) & mask) != 0) ||
	    ((le32_to_cpu(iagp->wmap[extno]) & mask) != 0) ||
	    (addressPXD(&iagp->inoext[extno]) == 0)) {
		if (amp)
			release_metapage(amp);
		if (bmp)
			release_metapage(bmp);

		jfs_error(imap->im_ipimap->i_sb, "iag inconsistent\n");
		return -EIO;
	}

	/* mark the inode as allocated in the working map.
	 */
	iagp->wmap[extno] |= cpu_to_le32(mask);

	/* check if all inodes within the extent are now
	 * allocated.  if so, update the free inode summary
	 * map to reflect this.
	 */
	if (iagp->wmap[extno] == cpu_to_le32(ONES)) {
		sword = extno >> L2EXTSPERSUM;
		bitno = extno & (EXTSPERSUM - 1);
		iagp->inosmap[sword] |= cpu_to_le32(HIGHORDER >> bitno);
	}

	/* if this was the last free inode in the iag, remove the
	 * iag from the ag free inode list.
	 */
	if (iagp->nfreeinos == cpu_to_le32(1)) {
		if (amp) {
			aiagp->inofreeback = iagp->inofreeback;
			write_metapage(amp);
		}

		if (bmp) {
			biagp->inofreefwd = iagp->inofreefwd;
			write_metapage(bmp);
		} else {
			imap->im_agctl[agno].inofree =
			    le32_to_cpu(iagp->inofreefwd);
		}
		iagp->inofreefwd = iagp->inofreeback = cpu_to_le32(-1);
	}

	/* update the free inode count at the iag, ag, inode
	 * map levels.
	 */
	le32_add_cpu(&iagp->nfreeinos, -1);
	imap->im_agctl[agno].numfree -= 1;
	atomic_dec(&imap->im_numfree);

	return (0);
}
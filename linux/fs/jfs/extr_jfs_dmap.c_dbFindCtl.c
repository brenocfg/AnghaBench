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
struct metapage {scalar_t__ data; } ;
struct dmapctl {int budmin; scalar_t__ leafidx; } ;
struct bmap {TYPE_1__* db_ipbmap; int /*<<< orphan*/  db_l2nbperpage; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  dmtree_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int BLKTOCTL (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTLLEAFIND ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  PSIZE ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int dbFindLeaf (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 struct metapage* read_metapage (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 

__attribute__((used)) static int dbFindCtl(struct bmap * bmp, int l2nb, int level, s64 * blkno)
{
	int rc, leafidx, lev;
	s64 b, lblkno;
	struct dmapctl *dcp;
	int budmin;
	struct metapage *mp;

	/* starting at the specified dmap control page level and block
	 * number, search down the dmap control levels for the starting
	 * block number of a dmap page that contains or starts off
	 * sufficient free blocks.
	 */
	for (lev = level, b = *blkno; lev >= 0; lev--) {
		/* get the buffer of the dmap control page for the block
		 * number and level (i.e. L0, L1, L2).
		 */
		lblkno = BLKTOCTL(b, bmp->db_l2nbperpage, lev);
		mp = read_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
		if (mp == NULL)
			return -EIO;
		dcp = (struct dmapctl *) mp->data;
		budmin = dcp->budmin;

		if (dcp->leafidx != cpu_to_le32(CTLLEAFIND)) {
			jfs_error(bmp->db_ipbmap->i_sb,
				  "Corrupt dmapctl page\n");
			release_metapage(mp);
			return -EIO;
		}

		/* search the tree within the dmap control page for
		 * sufficient free space.  if sufficient free space is found,
		 * dbFindLeaf() returns the index of the leaf at which
		 * free space was found.
		 */
		rc = dbFindLeaf((dmtree_t *) dcp, l2nb, &leafidx);

		/* release the buffer.
		 */
		release_metapage(mp);

		/* space found ?
		 */
		if (rc) {
			if (lev != level) {
				jfs_error(bmp->db_ipbmap->i_sb,
					  "dmap inconsistent\n");
				return -EIO;
			}
			return -ENOSPC;
		}

		/* adjust the block number to reflect the location within
		 * the dmap control page (i.e. the leaf) at which free
		 * space was found.
		 */
		b += (((s64) leafidx) << budmin);

		/* we stop the search at this dmap control page level if
		 * the number of blocks required is greater than or equal
		 * to the maximum number of blocks described at the next
		 * (lower) level.
		 */
		if (l2nb >= budmin)
			break;
	}

	*blkno = b;
	return (0);
}
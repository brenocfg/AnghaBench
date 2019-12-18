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
struct jfs_sb_info {int nbperpage; struct bmap* bmap; } ;
struct jfs_inode_info {scalar_t__ fileset; int active_ag; int /*<<< orphan*/  ag_lock; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct bmap {int db_maxfreebud; int /*<<< orphan*/ * db_active; } ;
typedef  int s64 ;

/* Variables and functions */
 int BLKTOAG (int,struct jfs_sb_info*) ; 
 int ENOSPC ; 
 scalar_t__ FILESYSTEM_I ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int dbAlloc (struct inode*,int,int,int*) ; 
 int /*<<< orphan*/  extRoundDown (int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
extBalloc(struct inode *ip, s64 hint, s64 * nblocks, s64 * blkno)
{
	struct jfs_inode_info *ji = JFS_IP(ip);
	struct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 nb, nblks, daddr, max;
	int rc, nbperpage = sbi->nbperpage;
	struct bmap *bmp = sbi->bmap;
	int ag;

	/* get the number of blocks to initially attempt to allocate.
	 * we'll first try the number of blocks requested unless this
	 * number is greater than the maximum number of contiguous free
	 * blocks in the map. in that case, we'll start off with the
	 * maximum free.
	 */
	max = (s64) 1 << bmp->db_maxfreebud;
	if (*nblocks >= max && *nblocks > nbperpage)
		nb = nblks = (max > nbperpage) ? max : nbperpage;
	else
		nb = nblks = *nblocks;

	/* try to allocate blocks */
	while ((rc = dbAlloc(ip, hint, nb, &daddr)) != 0) {
		/* if something other than an out of space error,
		 * stop and return this error.
		 */
		if (rc != -ENOSPC)
			return (rc);

		/* decrease the allocation request size */
		nb = min(nblks, extRoundDown(nb));

		/* give up if we cannot cover a page */
		if (nb < nbperpage)
			return (rc);
	}

	*nblocks = nb;
	*blkno = daddr;

	if (S_ISREG(ip->i_mode) && (ji->fileset == FILESYSTEM_I)) {
		ag = BLKTOAG(daddr, sbi);
		spin_lock_irq(&ji->ag_lock);
		if (ji->active_ag == -1) {
			atomic_inc(&bmp->db_active[ag]);
			ji->active_ag = ag;
		} else if (ji->active_ag != ag) {
			atomic_dec(&bmp->db_active[ji->active_ag]);
			atomic_inc(&bmp->db_active[ag]);
			ji->active_ag = ag;
		}
		spin_unlock_irq(&ji->ag_lock);
	}

	return (0);
}
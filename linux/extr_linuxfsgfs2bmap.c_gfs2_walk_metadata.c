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
typedef  int u64 ;
struct metapath {unsigned int mp_aheight; scalar_t__* mp_list; int /*<<< orphan*/ ** mp_bh; } ;
struct inode {int dummy; } ;
struct gfs2_sbd {int sd_inptrs; } ;
struct gfs2_inode {int i_height; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/ * (* gfs2_metadata_walker ) (struct metapath*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,void*) ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DIV_ROUND_UP_ULL (int,int) ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  const* WALK_NEXT ; 
 int /*<<< orphan*/  const* WALK_STOP ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clone_metapath (struct metapath*,struct metapath*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int fillup_metapath (struct gfs2_inode*,struct metapath*,int) ; 
 int /*<<< orphan*/ * metaend (unsigned int,struct metapath*) ; 
 int /*<<< orphan*/ * metapointer (unsigned int,struct metapath*) ; 
 int /*<<< orphan*/  release_metapath (struct metapath*) ; 

__attribute__((used)) static int gfs2_walk_metadata(struct inode *inode, sector_t lblock,
		u64 len, struct metapath *mp, gfs2_metadata_walker walker,
		void *data)
{
	struct metapath clone;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	const __be64 *start, *end, *ptr;
	u64 factor = 1;
	unsigned int hgt;
	int ret = 0;

	for (hgt = ip->i_height - 1; hgt >= mp->mp_aheight; hgt--)
		factor *= sdp->sd_inptrs;

	for (;;) {
		u64 step;

		/* Walk indirect block. */
		start = metapointer(hgt, mp);
		end = metaend(hgt, mp);

		step = (end - start) * factor;
		if (step > len)
			end = start + DIV_ROUND_UP_ULL(len, factor);

		ptr = walker(mp, start, end, factor, data);
		if (ptr == WALK_STOP)
			break;
		if (step >= len)
			break;
		len -= step;
		if (ptr != WALK_NEXT) {
			BUG_ON(!*ptr);
			mp->mp_list[hgt] += ptr - start;
			goto fill_up_metapath;
		}

lower_metapath:
		/* Decrease height of metapath. */
		if (mp != &clone) {
			clone_metapath(&clone, mp);
			mp = &clone;
		}
		brelse(mp->mp_bh[hgt]);
		mp->mp_bh[hgt] = NULL;
		if (!hgt)
			break;
		hgt--;
		factor *= sdp->sd_inptrs;

		/* Advance in metadata tree. */
		(mp->mp_list[hgt])++;
		start = metapointer(hgt, mp);
		end = metaend(hgt, mp);
		if (start >= end) {
			mp->mp_list[hgt] = 0;
			if (!hgt)
				break;
			goto lower_metapath;
		}

fill_up_metapath:
		/* Increase height of metapath. */
		if (mp != &clone) {
			clone_metapath(&clone, mp);
			mp = &clone;
		}
		ret = fillup_metapath(ip, mp, ip->i_height - 1);
		if (ret < 0)
			break;
		hgt += ret;
		for (; ret; ret--)
			do_div(factor, sdp->sd_inptrs);
		mp->mp_aheight = hgt + 1;
	}
	if (mp == &clone)
		release_metapath(mp);
	return ret;
}
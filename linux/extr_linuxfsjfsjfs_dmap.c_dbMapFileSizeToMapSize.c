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
typedef  int u32 ;
struct super_block {int dummy; } ;
struct inode {int i_size; struct super_block* i_sb; } ;
typedef  int s64 ;
struct TYPE_2__ {int l2bsize; int l2nbperpage; } ;

/* Variables and functions */
 int BMAPPGTOLEV (int) ; 
 TYPE_1__* JFS_SBI (struct super_block*) ; 
 int L2BPERDMAP ; 
 int LPERCTL ; 
 int MAXL0PAGES ; 
 int MAXL1PAGES ; 

s64 dbMapFileSizeToMapSize(struct inode * ipbmap)
{
	struct super_block *sb = ipbmap->i_sb;
	s64 nblocks;
	s64 npages, ndmaps;
	int level, i;
	int complete, factor;

	nblocks = ipbmap->i_size >> JFS_SBI(sb)->l2bsize;
	npages = nblocks >> JFS_SBI(sb)->l2nbperpage;
	level = BMAPPGTOLEV(npages);

	/* At each level, accumulate the number of dmap pages covered by
	 * the number of full child levels below it;
	 * repeat for the last incomplete child level.
	 */
	ndmaps = 0;
	npages--;		/* skip the first global control page */
	/* skip higher level control pages above top level covered by map */
	npages -= (2 - level);
	npages--;		/* skip top level's control page */
	for (i = level; i >= 0; i--) {
		factor =
		    (i == 2) ? MAXL1PAGES : ((i == 1) ? MAXL0PAGES : 1);
		complete = (u32) npages / factor;
		ndmaps += complete * ((i == 2) ? LPERCTL * LPERCTL :
				      ((i == 1) ? LPERCTL : 1));

		/* pages in last/incomplete child */
		npages = (u32) npages % factor;
		/* skip incomplete child's level control page */
		npages--;
	}

	/* convert the number of dmaps into the number of blocks
	 * which can be covered by the dmaps;
	 */
	nblocks = ndmaps << L2BPERDMAP;

	return (nblocks);
}
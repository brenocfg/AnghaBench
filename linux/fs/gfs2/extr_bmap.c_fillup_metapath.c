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
struct metapath {unsigned int mp_aheight; scalar_t__* mp_bh; } ;
struct gfs2_inode {int dummy; } ;

/* Variables and functions */
 int __fillup_metapath (struct gfs2_inode*,struct metapath*,unsigned int,int) ; 

__attribute__((used)) static int fillup_metapath(struct gfs2_inode *ip, struct metapath *mp, int h)
{
	unsigned int x = 0;
	int ret;

	if (h) {
		/* find the first buffer we need to look up. */
		for (x = h - 1; x > 0; x--) {
			if (mp->mp_bh[x])
				break;
		}
	}
	ret = __fillup_metapath(ip, mp, x, h);
	if (ret)
		return ret;
	return mp->mp_aheight - x - 1;
}
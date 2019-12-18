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
typedef  int /*<<< orphan*/  u64 ;
struct metapath {unsigned int mp_aheight; int /*<<< orphan*/ * mp_bh; } ;
struct gfs2_inode {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int gfs2_meta_indirect_buffer (struct gfs2_inode*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * metapointer (unsigned int,struct metapath*) ; 

__attribute__((used)) static int __fillup_metapath(struct gfs2_inode *ip, struct metapath *mp,
			     unsigned int x, unsigned int h)
{
	for (; x < h; x++) {
		__be64 *ptr = metapointer(x, mp);
		u64 dblock = be64_to_cpu(*ptr);
		int ret;

		if (!dblock)
			break;
		ret = gfs2_meta_indirect_buffer(ip, x + 1, dblock, &mp->mp_bh[x + 1]);
		if (ret)
			return ret;
	}
	mp->mp_aheight = x + 1;
	return 0;
}
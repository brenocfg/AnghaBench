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
struct vxfs_fsh {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct vxfs_fsh* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct vxfs_fsh*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* vxfs_bread (struct inode*,int) ; 

__attribute__((used)) static struct vxfs_fsh *
vxfs_getfsh(struct inode *ip, int which)
{
	struct buffer_head		*bp;

	bp = vxfs_bread(ip, which);
	if (bp) {
		struct vxfs_fsh		*fhp;

		if (!(fhp = kmalloc(sizeof(*fhp), GFP_KERNEL)))
			goto out;
		memcpy(fhp, bp->b_data, sizeof(*fhp));

		put_bh(bp);
		return (fhp);
	}
out:
	brelse(bp);
	return NULL;
}
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
struct gfs2_inode {int /*<<< orphan*/  i_rgd_gh; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_glock_dq_uninit (int /*<<< orphan*/ *) ; 
 scalar_t__ gfs2_holder_initialized (int /*<<< orphan*/ *) ; 

void gfs2_inplace_release(struct gfs2_inode *ip)
{
	if (gfs2_holder_initialized(&ip->i_rgd_gh))
		gfs2_glock_dq_uninit(&ip->i_rgd_gh);
}
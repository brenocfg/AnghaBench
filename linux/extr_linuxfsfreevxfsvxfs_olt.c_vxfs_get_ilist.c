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
struct vxfs_sb_info {int /*<<< orphan*/  vsi_iext; } ;
struct vxfs_oltilist {int /*<<< orphan*/ * olt_iext; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs32_to_cpu (struct vxfs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vxfs_get_ilist(struct vxfs_oltilist *ilistp, struct vxfs_sb_info *infp)
{
	BUG_ON(infp->vsi_iext);
	infp->vsi_iext = fs32_to_cpu(infp, ilistp->olt_iext[0]);
}
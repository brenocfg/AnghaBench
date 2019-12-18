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
struct ocfs2_meta_lvb {scalar_t__ lvb_version; int /*<<< orphan*/  lvb_igeneration; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_lksb; } ;
struct inode {scalar_t__ i_generation; } ;

/* Variables and functions */
 scalar_t__ OCFS2_LVB_VERSION ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ocfs2_meta_lvb* ocfs2_dlm_lvb (int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_dlm_lvb_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ocfs2_meta_lvb_is_trustable(struct inode *inode,
					      struct ocfs2_lock_res *lockres)
{
	struct ocfs2_meta_lvb *lvb = ocfs2_dlm_lvb(&lockres->l_lksb);

	if (ocfs2_dlm_lvb_valid(&lockres->l_lksb)
	    && lvb->lvb_version == OCFS2_LVB_VERSION
	    && be32_to_cpu(lvb->lvb_igeneration) == inode->i_generation)
		return 1;
	return 0;
}
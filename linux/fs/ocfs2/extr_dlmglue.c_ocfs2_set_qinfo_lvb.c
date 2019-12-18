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
struct ocfs2_qinfo_lvb {void* lvb_free_entry; void* lvb_free_blk; void* lvb_blocks; void* lvb_syncms; void* lvb_igrace; void* lvb_bgrace; int /*<<< orphan*/  lvb_version; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqi_free_entry; int /*<<< orphan*/  dqi_free_blk; int /*<<< orphan*/  dqi_blocks; int /*<<< orphan*/  dqi_type; int /*<<< orphan*/  dqi_sb; } ;
struct ocfs2_mem_dqinfo {TYPE_1__ dqi_gi; int /*<<< orphan*/  dqi_syncms; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_lksb; } ;
struct mem_dqinfo {int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_QINFO_LVB_VERSION ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct ocfs2_qinfo_lvb* ocfs2_dlm_lvb (int /*<<< orphan*/ *) ; 
 struct ocfs2_mem_dqinfo* ocfs2_lock_res_qinfo (struct ocfs2_lock_res*) ; 
 struct mem_dqinfo* sb_dqinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_set_qinfo_lvb(struct ocfs2_lock_res *lockres)
{
	struct ocfs2_qinfo_lvb *lvb;
	struct ocfs2_mem_dqinfo *oinfo = ocfs2_lock_res_qinfo(lockres);
	struct mem_dqinfo *info = sb_dqinfo(oinfo->dqi_gi.dqi_sb,
					    oinfo->dqi_gi.dqi_type);

	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	lvb->lvb_version = OCFS2_QINFO_LVB_VERSION;
	lvb->lvb_bgrace = cpu_to_be32(info->dqi_bgrace);
	lvb->lvb_igrace = cpu_to_be32(info->dqi_igrace);
	lvb->lvb_syncms = cpu_to_be32(oinfo->dqi_syncms);
	lvb->lvb_blocks = cpu_to_be32(oinfo->dqi_gi.dqi_blocks);
	lvb->lvb_free_blk = cpu_to_be32(oinfo->dqi_gi.dqi_free_blk);
	lvb->lvb_free_entry = cpu_to_be32(oinfo->dqi_gi.dqi_free_entry);
}
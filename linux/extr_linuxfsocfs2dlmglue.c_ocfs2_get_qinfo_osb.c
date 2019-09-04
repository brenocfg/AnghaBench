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
struct ocfs2_super {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqi_sb; } ;
struct ocfs2_mem_dqinfo {TYPE_1__ dqi_gi; } ;
struct ocfs2_lock_res {struct ocfs2_mem_dqinfo* l_priv; } ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ocfs2_super *ocfs2_get_qinfo_osb(struct ocfs2_lock_res *lockres)
{
	struct ocfs2_mem_dqinfo *info = lockres->l_priv;

	return OCFS2_SB(info->dqi_gi.dqi_sb);
}
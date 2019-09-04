#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_3__ {int dqi_qtree_depth; } ;
struct ocfs2_mem_dqinfo {TYPE_1__ dqi_gi; } ;
struct TYPE_4__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 TYPE_2__* sb_dqinfo (struct super_block*,int) ; 

__attribute__((used)) static int ocfs2_global_qinit_alloc(struct super_block *sb, int type)
{
	struct ocfs2_mem_dqinfo *oinfo = sb_dqinfo(sb, type)->dqi_priv;

	/*
	 * We may need to allocate tree blocks and a leaf block but not the
	 * root block
	 */
	return oinfo->dqi_gi.dqi_qtree_depth;
}
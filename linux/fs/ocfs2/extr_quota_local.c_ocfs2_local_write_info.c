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
struct super_block {int dummy; } ;
struct ocfs2_mem_dqinfo {struct buffer_head* dqi_libh; } ;
struct mem_dqinfo {scalar_t__ dqi_priv; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * files; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_modify_bh (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ,struct mem_dqinfo*) ; 
 int /*<<< orphan*/  olq_update_info ; 
 struct mem_dqinfo* sb_dqinfo (struct super_block*,int) ; 
 TYPE_1__* sb_dqopt (struct super_block*) ; 

__attribute__((used)) static int ocfs2_local_write_info(struct super_block *sb, int type)
{
	struct mem_dqinfo *info = sb_dqinfo(sb, type);
	struct buffer_head *bh = ((struct ocfs2_mem_dqinfo *)info->dqi_priv)
						->dqi_libh;
	int status;

	status = ocfs2_modify_bh(sb_dqopt(sb)->files[type], bh, olq_update_info,
				 info);
	if (status < 0) {
		mlog_errno(status);
		return -1;
	}

	return 0;
}
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
struct ocfs2_mem_dqinfo {int /*<<< orphan*/  dqi_blocks; int /*<<< orphan*/  dqi_chunks; int /*<<< orphan*/  dqi_flags; } ;
struct ocfs2_local_disk_dqinfo {void* dqi_blocks; void* dqi_chunks; void* dqi_flags; } ;
struct mem_dqinfo {struct ocfs2_mem_dqinfo* dqi_priv; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ OCFS2_LOCAL_INFO_OFF ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void olq_update_info(struct buffer_head *bh, void *private)
{
	struct mem_dqinfo *info = private;
	struct ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	struct ocfs2_local_disk_dqinfo *ldinfo;

	ldinfo = (struct ocfs2_local_disk_dqinfo *)(bh->b_data +
						OCFS2_LOCAL_INFO_OFF);
	spin_lock(&dq_data_lock);
	ldinfo->dqi_flags = cpu_to_le32(oinfo->dqi_flags);
	ldinfo->dqi_chunks = cpu_to_le32(oinfo->dqi_chunks);
	ldinfo->dqi_blocks = cpu_to_le32(oinfo->dqi_blocks);
	spin_unlock(&dq_data_lock);
}
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
struct nvme_queue {size_t sq_tail; size_t q_depth; int /*<<< orphan*/  sq_lock; int /*<<< orphan*/  q_db; int /*<<< orphan*/  dbbuf_sq_ei; int /*<<< orphan*/  dbbuf_sq_db; int /*<<< orphan*/ * sq_cmds; int /*<<< orphan*/ * sq_cmds_io; } ;
struct nvme_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct nvme_command*,int) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,struct nvme_command*,int) ; 
 scalar_t__ nvme_dbbuf_update_and_check_event (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_submit_cmd(struct nvme_queue *nvmeq, struct nvme_command *cmd)
{
	spin_lock(&nvmeq->sq_lock);
	if (nvmeq->sq_cmds_io)
		memcpy_toio(&nvmeq->sq_cmds_io[nvmeq->sq_tail], cmd,
				sizeof(*cmd));
	else
		memcpy(&nvmeq->sq_cmds[nvmeq->sq_tail], cmd, sizeof(*cmd));

	if (++nvmeq->sq_tail == nvmeq->q_depth)
		nvmeq->sq_tail = 0;
	if (nvme_dbbuf_update_and_check_event(nvmeq->sq_tail,
			nvmeq->dbbuf_sq_db, nvmeq->dbbuf_sq_ei))
		writel(nvmeq->sq_tail, nvmeq->q_db);
	spin_unlock(&nvmeq->sq_lock);
}
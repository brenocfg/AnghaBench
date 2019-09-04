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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  admin_q; } ;
struct nvme_dev {TYPE_2__ ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  qid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ delete_queue; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adapter_delete_queue(struct nvme_dev *dev, u8 opcode, u16 id)
{
	struct nvme_command c;

	memset(&c, 0, sizeof(c));
	c.delete_queue.opcode = opcode;
	c.delete_queue.qid = cpu_to_le16(id);

	return nvme_submit_sync_cmd(dev->ctrl.admin_q, &c, NULL, 0);
}
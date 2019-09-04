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
typedef  int /*<<< orphan*/  u8 ;
struct nvme_dev {int online_queues; int /*<<< orphan*/  ioq_wait; int /*<<< orphan*/ * queues; } ;

/* Variables and functions */
 unsigned long ADMIN_TIMEOUT ; 
 int /*<<< orphan*/  nvme_admin_delete_cq ; 
 int /*<<< orphan*/  nvme_admin_delete_sq ; 
 scalar_t__ nvme_delete_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_io_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nvme_disable_io_queues(struct nvme_dev *dev)
{
	int pass, queues = dev->online_queues - 1;
	unsigned long timeout;
	u8 opcode = nvme_admin_delete_sq;

	for (pass = 0; pass < 2; pass++) {
		int sent = 0, i = queues;

		reinit_completion(&dev->ioq_wait);
 retry:
		timeout = ADMIN_TIMEOUT;
		for (; i > 0; i--, sent++)
			if (nvme_delete_queue(&dev->queues[i], opcode))
				break;

		while (sent--) {
			timeout = wait_for_completion_io_timeout(&dev->ioq_wait, timeout);
			if (timeout == 0)
				return;
			if (i)
				goto retry;
		}
		opcode = nvme_admin_delete_cq;
	}
}
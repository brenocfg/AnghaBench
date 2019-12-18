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
struct transaction_queue {unsigned int size; scalar_t__ state; int /*<<< orphan*/  list; struct fw_unit* unit; int /*<<< orphan*/  wait; scalar_t__ seqnum; void* buf; } ;
struct snd_efw_transaction {int /*<<< orphan*/  seqnum; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFC_TIMEOUT_MS ; 
 int EIO ; 
 int /*<<< orphan*/  ERROR_DELAY_MS ; 
 unsigned int ERROR_RETRIES ; 
 scalar_t__ STATE_BUS_RESET ; 
 scalar_t__ STATE_COMPLETE ; 
 scalar_t__ STATE_PENDING ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int snd_efw_transaction_cmd (struct fw_unit*,void*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transaction_queues ; 
 int /*<<< orphan*/  transaction_queues_lock ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int snd_efw_transaction_run(struct fw_unit *unit,
			    const void *cmd, unsigned int cmd_size,
			    void *resp, unsigned int resp_size)
{
	struct transaction_queue t;
	unsigned int tries;
	int ret;

	t.unit = unit;
	t.buf = resp;
	t.size = resp_size;
	t.seqnum = be32_to_cpu(((struct snd_efw_transaction *)cmd)->seqnum) + 1;
	t.state = STATE_PENDING;
	init_waitqueue_head(&t.wait);

	spin_lock_irq(&transaction_queues_lock);
	list_add_tail(&t.list, &transaction_queues);
	spin_unlock_irq(&transaction_queues_lock);

	tries = 0;
	do {
		ret = snd_efw_transaction_cmd(t.unit, (void *)cmd, cmd_size);
		if (ret < 0)
			break;

		wait_event_timeout(t.wait, t.state != STATE_PENDING,
				   msecs_to_jiffies(EFC_TIMEOUT_MS));

		if (t.state == STATE_COMPLETE) {
			ret = t.size;
			break;
		} else if (t.state == STATE_BUS_RESET) {
			msleep(ERROR_DELAY_MS);
		} else if (++tries >= ERROR_RETRIES) {
			dev_err(&t.unit->device, "EFW transaction timed out\n");
			ret = -EIO;
			break;
		}
	} while (1);

	spin_lock_irq(&transaction_queues_lock);
	list_del(&t.list);
	spin_unlock_irq(&transaction_queues_lock);

	return ret;
}
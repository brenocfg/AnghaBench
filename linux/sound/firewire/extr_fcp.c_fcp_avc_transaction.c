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
typedef  int u8 ;
struct fw_unit {int /*<<< orphan*/  device; } ;
struct fcp_transaction {unsigned int response_size; unsigned int response_match_bytes; scalar_t__ state; int deferrable; int /*<<< orphan*/  list; struct fw_unit* unit; int /*<<< orphan*/  wait; void* response_buffer; } ;

/* Variables and functions */
 scalar_t__ CSR_FCP_COMMAND ; 
 scalar_t__ CSR_REGISTER_BASE ; 
 int EIO ; 
 int /*<<< orphan*/  ERROR_DELAY_MS ; 
 int ERROR_RETRIES ; 
 int /*<<< orphan*/  FCP_TIMEOUT_MS ; 
 scalar_t__ STATE_BUS_RESET ; 
 scalar_t__ STATE_COMPLETE ; 
 scalar_t__ STATE_DEFERRED ; 
 scalar_t__ STATE_PENDING ; 
 int TCODE_WRITE_BLOCK_REQUEST ; 
 int TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int snd_fw_transaction (struct fw_unit*,int,scalar_t__,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transactions ; 
 int /*<<< orphan*/  transactions_lock ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int fcp_avc_transaction(struct fw_unit *unit,
			const void *command, unsigned int command_size,
			void *response, unsigned int response_size,
			unsigned int response_match_bytes)
{
	struct fcp_transaction t;
	int tcode, ret, tries = 0;

	t.unit = unit;
	t.response_buffer = response;
	t.response_size = response_size;
	t.response_match_bytes = response_match_bytes;
	t.state = STATE_PENDING;
	init_waitqueue_head(&t.wait);

	if (*(const u8 *)command == 0x00 || *(const u8 *)command == 0x03)
		t.deferrable = true;

	spin_lock_irq(&transactions_lock);
	list_add_tail(&t.list, &transactions);
	spin_unlock_irq(&transactions_lock);

	for (;;) {
		tcode = command_size == 4 ? TCODE_WRITE_QUADLET_REQUEST
					  : TCODE_WRITE_BLOCK_REQUEST;
		ret = snd_fw_transaction(t.unit, tcode,
					 CSR_REGISTER_BASE + CSR_FCP_COMMAND,
					 (void *)command, command_size, 0);
		if (ret < 0)
			break;
deferred:
		wait_event_timeout(t.wait, t.state != STATE_PENDING,
				   msecs_to_jiffies(FCP_TIMEOUT_MS));

		if (t.state == STATE_DEFERRED) {
			/*
			 * 'AV/C General Specification' define no time limit
			 * on command completion once an INTERIM response has
			 * been sent. but we promise to finish this function
			 * for a caller. Here we use FCP_TIMEOUT_MS for next
			 * interval. This is not in the specification.
			 */
			t.state = STATE_PENDING;
			goto deferred;
		} else if (t.state == STATE_COMPLETE) {
			ret = t.response_size;
			break;
		} else if (t.state == STATE_BUS_RESET) {
			msleep(ERROR_DELAY_MS);
		} else if (++tries >= ERROR_RETRIES) {
			dev_err(&t.unit->device, "FCP command timed out\n");
			ret = -EIO;
			break;
		}
	}

	spin_lock_irq(&transactions_lock);
	list_del(&t.list);
	spin_unlock_irq(&transactions_lock);

	return ret;
}
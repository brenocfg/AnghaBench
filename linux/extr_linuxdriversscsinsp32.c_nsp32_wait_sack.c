#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int BaseAddress; } ;
typedef  TYPE_1__ nsp32_hw_data ;

/* Variables and functions */
 int ASSERT ; 
 unsigned char BUSMON_ACK ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int NEGATE ; 
 int /*<<< orphan*/  NSP32_DEBUG_WAIT ; 
 int REQSACK_TIMEOUT_TIME ; 
 int /*<<< orphan*/  SCSI_BUS_MONITOR ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*,...) ; 
 unsigned char nsp32_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void nsp32_wait_sack(nsp32_hw_data *data, int state)
{
	unsigned int  base      = data->BaseAddress;
	int           wait_time = 0;
	unsigned char bus, ack_bit;

	if (!((state == ASSERT) || (state == NEGATE))) {
		nsp32_msg(KERN_ERR, "unknown state designation");
	}
	/* ACK is BIT(4) */
	ack_bit = (state == ASSERT ? BUSMON_ACK : 0);

	do {
		bus = nsp32_read1(base, SCSI_BUS_MONITOR);
		if ((bus & BUSMON_ACK) == ack_bit) {
			nsp32_dbg(NSP32_DEBUG_WAIT,
				  "wait_time: %d", wait_time);
			return;
		}
		udelay(1);
		wait_time++;
	} while (wait_time < REQSACK_TIMEOUT_TIME);

	nsp32_msg(KERN_WARNING, "wait SACK timeout, ack_bit: 0x%x", ack_bit);
}
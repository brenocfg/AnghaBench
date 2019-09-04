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
struct TYPE_2__ {scalar_t__ mode; } ;
struct slgt_info {int /*<<< orphan*/  tx_timer; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int tbuf_bytes (struct slgt_info*) ; 

__attribute__((used)) static void update_tx_timer(struct slgt_info *info)
{
	/*
	 * use worst case speed of 1200bps to calculate transmit timeout
	 * based on data in buffers (tbuf_bytes) and FIFO (128 bytes)
	 */
	if (info->params.mode == MGSL_MODE_HDLC) {
		int timeout  = (tbuf_bytes(info) * 7) + 1000;
		mod_timer(&info->tx_timer, jiffies + msecs_to_jiffies(timeout));
	}
}
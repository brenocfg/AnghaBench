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
struct ipw_tx_packet {int /*<<< orphan*/  queue; } ;
struct ipw_hardware {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_queued; int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_packets_to_hw (struct ipw_hardware*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void send_packet(struct ipw_hardware *hw, int priority,
			struct ipw_tx_packet *packet)
{
	unsigned long flags;

	spin_lock_irqsave(&hw->lock, flags);
	list_add_tail(&packet->queue, &hw->tx_queue[priority]);
	hw->tx_queued++;
	spin_unlock_irqrestore(&hw->lock, flags);

	flush_packets_to_hw(hw);
}
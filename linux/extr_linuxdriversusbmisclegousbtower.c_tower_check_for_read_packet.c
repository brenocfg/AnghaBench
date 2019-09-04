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
struct lego_usb_tower {scalar_t__ read_buffer_length; scalar_t__ read_packet_length; int /*<<< orphan*/  read_buffer_lock; scalar_t__ interrupt_in_done; scalar_t__ packet_timeout_jiffies; scalar_t__ read_last_arrival; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  packet_timeout ; 
 scalar_t__ read_buffer_size ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tower_check_for_read_packet (struct lego_usb_tower *dev)
{
	spin_lock_irq (&dev->read_buffer_lock);
	if (!packet_timeout
	    || time_after(jiffies, dev->read_last_arrival + dev->packet_timeout_jiffies)
	    || dev->read_buffer_length == read_buffer_size) {
		dev->read_packet_length = dev->read_buffer_length;
	}
	dev->interrupt_in_done = 0;
	spin_unlock_irq (&dev->read_buffer_lock);
}
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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  cr_int_addr; int /*<<< orphan*/  completion; } ;
struct zd_usb_interrupt {TYPE_1__ read_regs; int /*<<< orphan*/  read_regs_enabled; int /*<<< orphan*/  interval; int /*<<< orphan*/  lock; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;

/* Variables and functions */
 scalar_t__ CR_INTERRUPT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_urb_interval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_usb_to_usbdev (struct zd_usb*) ; 

__attribute__((used)) static inline void init_usb_interrupt(struct zd_usb *usb)
{
	struct zd_usb_interrupt *intr = &usb->intr;

	spin_lock_init(&intr->lock);
	intr->interval = int_urb_interval(zd_usb_to_usbdev(usb));
	init_completion(&intr->read_regs.completion);
	atomic_set(&intr->read_regs_enabled, 0);
	intr->read_regs.cr_int_addr = cpu_to_le16((u16)CR_INTERRUPT);
}
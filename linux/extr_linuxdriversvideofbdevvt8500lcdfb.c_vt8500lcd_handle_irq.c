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
struct vt8500lcd_info {scalar_t__ regbase; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t vt8500lcd_handle_irq(int irq, void *dev_id)
{
	struct vt8500lcd_info *fbi = dev_id;

	if (readl(fbi->regbase + 0x38) & (1 << 3))
		wake_up_interruptible(&fbi->wait);

	writel(0xffffffff, fbi->regbase + 0x38);
	return IRQ_HANDLED;
}
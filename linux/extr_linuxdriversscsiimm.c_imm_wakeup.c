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
struct TYPE_3__ {scalar_t__ wanted; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ imm_struct ;

/* Variables and functions */
 int /*<<< orphan*/  arbitration_lock ; 
 int /*<<< orphan*/  got_it (TYPE_1__*) ; 
 scalar_t__ parport_claim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void imm_wakeup(void *ref)
{
	imm_struct *dev = (imm_struct *) ref;
	unsigned long flags;

	spin_lock_irqsave(&arbitration_lock, flags);
	if (dev->wanted) {
		if (parport_claim(dev->dev) == 0) {
			got_it(dev);
			dev->wanted = 0;
		}
	}
	spin_unlock_irqrestore(&arbitration_lock, flags);
}
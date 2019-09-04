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
typedef  int u32 ;
struct rfkill {int state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int RFKILL_BLOCK_ANY ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool rfkill_blocked(struct rfkill *rfkill)
{
	unsigned long flags;
	u32 state;

	spin_lock_irqsave(&rfkill->lock, flags);
	state = rfkill->state;
	spin_unlock_irqrestore(&rfkill->lock, flags);

	return !!(state & RFKILL_BLOCK_ANY);
}
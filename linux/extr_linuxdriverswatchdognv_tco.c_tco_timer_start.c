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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  TCO_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCO_CNT_TCOHALT ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tco_lock ; 
 int /*<<< orphan*/  tcobase ; 

__attribute__((used)) static void tco_timer_start(void)
{
	u32 val;
	unsigned long flags;

	spin_lock_irqsave(&tco_lock, flags);
	val = inl(TCO_CNT(tcobase));
	val &= ~TCO_CNT_TCOHALT;
	outl(val, TCO_CNT(tcobase));
	spin_unlock_irqrestore(&tco_lock, flags);
}
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
struct wm0010_priv {int state; int boot_failed; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_lock; } ;
typedef  enum wm0010_state { ____Placeholder_wm0010_state } wm0010_state ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wm0010_state_to_str (int) ; 

__attribute__((used)) static void wm0010_mark_boot_failure(struct wm0010_priv *wm0010)
{
	enum wm0010_state state;
	unsigned long flags;

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	state = wm0010->state;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	dev_err(wm0010->dev, "Failed to transition from `%s' state to `%s' state\n",
		wm0010_state_to_str(state), wm0010_state_to_str(state + 1));

	wm0010->boot_failed = true;
}
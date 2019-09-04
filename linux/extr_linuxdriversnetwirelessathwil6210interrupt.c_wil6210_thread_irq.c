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
struct wil6210_priv {int suspend_resp_comp; int /*<<< orphan*/  wq; scalar_t__ suspend_resp_rcvd; scalar_t__ isr_misc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil6210_irq_misc_thread (int,void*) ; 
 int /*<<< orphan*/  wil6210_unmask_irq_pseudo (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_dbg_irq (struct wil6210_priv*,char*) ; 

__attribute__((used)) static irqreturn_t wil6210_thread_irq(int irq, void *cookie)
{
	struct wil6210_priv *wil = cookie;

	wil_dbg_irq(wil, "Thread IRQ\n");
	/* Discover real IRQ cause */
	if (wil->isr_misc)
		wil6210_irq_misc_thread(irq, cookie);

	wil6210_unmask_irq_pseudo(wil);

	if (wil->suspend_resp_rcvd) {
		wil_dbg_irq(wil, "set suspend_resp_comp to true\n");
		wil->suspend_resp_comp = true;
		wake_up_interruptible(&wil->wq);
	}

	return IRQ_HANDLED;
}
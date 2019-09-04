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
struct wil6210_priv {int n_msi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_mask_irq (struct wil6210_priv*) ; 

void wil6210_fini_irq(struct wil6210_priv *wil, int irq)
{
	wil_dbg_misc(wil, "fini_irq:\n");

	wil_mask_irq(wil);
	free_irq(irq, wil);
	if (wil->n_msi == 3) {
		free_irq(irq + 1, wil);
		free_irq(irq + 2, wil);
	}
}
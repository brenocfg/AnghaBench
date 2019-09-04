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
struct wil6210_priv {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGF_DMA_PSEUDO_CAUSE_MASK_SW ; 
 int /*<<< orphan*/  WIL6210_IRQ_DISABLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_irq (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_status_irqen ; 
 int /*<<< orphan*/  wil_w (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wil6210_mask_irq_pseudo(struct wil6210_priv *wil)
{
	wil_dbg_irq(wil, "mask_irq_pseudo\n");

	wil_w(wil, RGF_DMA_PSEUDO_CAUSE_MASK_SW, WIL6210_IRQ_DISABLE);

	clear_bit(wil_status_irqen, wil->status);
}
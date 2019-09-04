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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ (* irq_rx ) (int,void*) ;scalar_t__ (* irq_tx ) (int,void*) ;} ;
struct wil6210_priv {TYPE_1__ txrx_ops; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 int BIT_DMA_PSEUDO_CAUSE_MISC ; 
 int BIT_DMA_PSEUDO_CAUSE_RX ; 
 int BIT_DMA_PSEUDO_CAUSE_TX ; 
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 scalar_t__ IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  RGF_DMA_PSEUDO_CAUSE ; 
 scalar_t__ stub1 (int,void*) ; 
 scalar_t__ stub2 (int,void*) ; 
 int /*<<< orphan*/  trace_wil6210_irq_pseudo (int) ; 
 scalar_t__ unlikely (int) ; 
 int wil6210_debug_irq_mask (struct wil6210_priv*,int) ; 
 scalar_t__ wil6210_irq_misc (int,void*) ; 
 int /*<<< orphan*/  wil6210_mask_irq_pseudo (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil6210_unmask_irq_pseudo (struct wil6210_priv*) ; 
 int /*<<< orphan*/  wil_dbg_irq (struct wil6210_priv*,char*,int) ; 
 int wil_r (struct wil6210_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t wil6210_hardirq(int irq, void *cookie)
{
	irqreturn_t rc = IRQ_HANDLED;
	struct wil6210_priv *wil = cookie;
	u32 pseudo_cause = wil_r(wil, RGF_DMA_PSEUDO_CAUSE);

	/**
	 * pseudo_cause is Clear-On-Read, no need to ACK
	 */
	if (unlikely((pseudo_cause == 0) || ((pseudo_cause & 0xff) == 0xff)))
		return IRQ_NONE;

	/* IRQ mask debug */
	if (unlikely(wil6210_debug_irq_mask(wil, pseudo_cause)))
		return IRQ_NONE;

	trace_wil6210_irq_pseudo(pseudo_cause);
	wil_dbg_irq(wil, "Pseudo IRQ 0x%08x\n", pseudo_cause);

	wil6210_mask_irq_pseudo(wil);

	/* Discover real IRQ cause
	 * There are 2 possible phases for every IRQ:
	 * - hard IRQ handler called right here
	 * - threaded handler called later
	 *
	 * Hard IRQ handler reads and clears ISR.
	 *
	 * If threaded handler requested, hard IRQ handler
	 * returns IRQ_WAKE_THREAD and saves ISR register value
	 * for the threaded handler use.
	 *
	 * voting for wake thread - need at least 1 vote
	 */
	if ((pseudo_cause & BIT_DMA_PSEUDO_CAUSE_RX) &&
	    (wil->txrx_ops.irq_rx(irq, cookie) == IRQ_WAKE_THREAD))
		rc = IRQ_WAKE_THREAD;

	if ((pseudo_cause & BIT_DMA_PSEUDO_CAUSE_TX) &&
	    (wil->txrx_ops.irq_tx(irq, cookie) == IRQ_WAKE_THREAD))
		rc = IRQ_WAKE_THREAD;

	if ((pseudo_cause & BIT_DMA_PSEUDO_CAUSE_MISC) &&
	    (wil6210_irq_misc(irq, cookie) == IRQ_WAKE_THREAD))
		rc = IRQ_WAKE_THREAD;

	/* if thread is requested, it will unmask IRQ */
	if (rc != IRQ_WAKE_THREAD)
		wil6210_unmask_irq_pseudo(wil);

	return rc;
}
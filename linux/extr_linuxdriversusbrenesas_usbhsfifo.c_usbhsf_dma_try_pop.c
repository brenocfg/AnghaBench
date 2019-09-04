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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_usb_dmac ; 
 int /*<<< orphan*/  usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (int /*<<< orphan*/ ) ; 
 int usbhsf_dma_try_pop_with_rx_irq (struct usbhs_pkt*,int*) ; 

__attribute__((used)) static int usbhsf_dma_try_pop(struct usbhs_pkt *pkt, int *is_done)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pkt->pipe);

	BUG_ON(usbhs_get_dparam(priv, has_usb_dmac));

	return usbhsf_dma_try_pop_with_rx_irq(pkt, is_done);
}
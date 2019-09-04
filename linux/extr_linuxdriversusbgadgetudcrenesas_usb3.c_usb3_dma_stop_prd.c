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
struct renesas_usb3_ep {int /*<<< orphan*/  num; struct renesas_usb3_dma* dma; } ;
struct renesas_usb3_dma {int /*<<< orphan*/  num; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_DMA_CH0_CON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_disable_dma_irq (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_dma_stop_prd(struct renesas_usb3_ep *usb3_ep)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	struct renesas_usb3_dma *dma = usb3_ep->dma;

	usb3_disable_dma_irq(usb3, usb3_ep->num);
	usb3_write(usb3, 0, USB3_DMA_CH0_CON(dma->num));
}
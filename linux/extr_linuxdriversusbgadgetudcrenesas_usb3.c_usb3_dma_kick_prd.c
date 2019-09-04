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
struct renesas_usb3_ep {int num; scalar_t__ dir_in; struct renesas_usb3_dma* dma; } ;
struct renesas_usb3_dma {int prd_dma; int /*<<< orphan*/  num; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int AXI_INT_PRDEN_CLR_STA (int /*<<< orphan*/ ) ; 
 int AXI_INT_PRDERR_STA (int /*<<< orphan*/ ) ; 
 int DMA_COM_PIPE_NO (int) ; 
 int DMA_CON_PIPE_DIR ; 
 int DMA_CON_PRD_EN ; 
 int /*<<< orphan*/  USB3_AXI_INT_STA ; 
 int /*<<< orphan*/  USB3_DMA_CH0_CON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB3_DMA_CH0_PRD_ADR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB3_DMA_INT_STA ; 
 int /*<<< orphan*/  usb3_enable_dma_irq (struct renesas_usb3*,int) ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void usb3_dma_kick_prd(struct renesas_usb3_ep *usb3_ep)
{
	struct renesas_usb3_dma *dma = usb3_ep->dma;
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 dma_con = DMA_COM_PIPE_NO(usb3_ep->num) | DMA_CON_PRD_EN;

	if (usb3_ep->dir_in)
		dma_con |= DMA_CON_PIPE_DIR;

	wmb();	/* prd entries should be in system memory here */

	usb3_write(usb3, 1 << usb3_ep->num, USB3_DMA_INT_STA);
	usb3_write(usb3, AXI_INT_PRDEN_CLR_STA(dma->num) |
		   AXI_INT_PRDERR_STA(dma->num), USB3_AXI_INT_STA);

	usb3_write(usb3, dma->prd_dma, USB3_DMA_CH0_PRD_ADR(dma->num));
	usb3_write(usb3, dma_con, USB3_DMA_CH0_CON(dma->num));
	usb3_enable_dma_irq(usb3, usb3_ep->num);
}
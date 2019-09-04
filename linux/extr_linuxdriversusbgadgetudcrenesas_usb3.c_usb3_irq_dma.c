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
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_DMA_INT_ENA ; 
 int /*<<< orphan*/  USB3_DMA_INT_STA ; 
 int /*<<< orphan*/  usb3_irq_dma_int (struct renesas_usb3*,int) ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_irq_dma(struct renesas_usb3 *usb3)
{
	u32 dma_sta = usb3_read(usb3, USB3_DMA_INT_STA);

	dma_sta &= usb3_read(usb3, USB3_DMA_INT_ENA);
	if (dma_sta) {
		usb3_write(usb3, dma_sta, USB3_DMA_INT_STA);
		usb3_irq_dma_int(usb3, dma_sta);
	}
}
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
struct TYPE_2__ {unsigned int conn_table; } ;

/* Variables and functions */
 int FIRST_QSB_QID ; 
 int* MBOX_IGU1_ISR ; 
 int* MBOX_IGU1_ISRC ; 
 int /*<<< orphan*/  PPE_MAILBOX_IGU1_INT ; 
 int RX_DMA_CH_AAL ; 
 int RX_DMA_CH_OAM ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 TYPE_1__ g_atm_priv_data ; 
 int /*<<< orphan*/  g_dma_tasklet ; 
 int /*<<< orphan*/  mailbox_aal_rx_handler () ; 
 int /*<<< orphan*/  mailbox_oam_rx_handler () ; 
 int /*<<< orphan*/  mailbox_tx_handler (unsigned int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_ppe_tasklet(unsigned long data)
{
	unsigned int irqs = *MBOX_IGU1_ISR;
	*MBOX_IGU1_ISRC = *MBOX_IGU1_ISR;

	if (irqs & (1 << RX_DMA_CH_AAL))
		mailbox_aal_rx_handler();
	if (irqs & (1 << RX_DMA_CH_OAM))
		mailbox_oam_rx_handler();

	/* any valid tx irqs */
	if ((irqs >> (FIRST_QSB_QID + 16)) & g_atm_priv_data.conn_table)
		mailbox_tx_handler(irqs >> (FIRST_QSB_QID + 16));

	if ((*MBOX_IGU1_ISR & ((1 << RX_DMA_CH_AAL) | (1 << RX_DMA_CH_OAM))) != 0)
		tasklet_schedule(&g_dma_tasklet);
	else if (*MBOX_IGU1_ISR >> (FIRST_QSB_QID + 16)) /* TX queue */
		tasklet_schedule(&g_dma_tasklet);
	else
		enable_irq(PPE_MAILBOX_IGU1_INT);
}
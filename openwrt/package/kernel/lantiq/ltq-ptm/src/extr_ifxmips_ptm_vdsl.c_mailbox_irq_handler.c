#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx_descriptor {scalar_t__ own; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* itf; } ;
struct TYPE_3__ {size_t rx_desc_pos; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 unsigned int IFX_REG_R32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_REG_W32 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_REG_W32_MASK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MBOX_IGU1_IER ; 
 int /*<<< orphan*/  MBOX_IGU1_ISR ; 
 int /*<<< orphan*/  MBOX_IGU1_ISRC ; 
 struct rx_descriptor* WAN_RX_DESC_BASE ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/ * g_net_dev ; 
 TYPE_2__ g_ptm_priv_data ; 
 int /*<<< orphan*/  g_swap_desc_tasklet ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mailbox_irq_handler(int irq, void *dev_id)
{
    unsigned int isr;
    int i;

    isr = IFX_REG_R32(MBOX_IGU1_ISR);
    IFX_REG_W32(isr, MBOX_IGU1_ISRC);
    isr &= IFX_REG_R32(MBOX_IGU1_IER);

            if (isr & BIT(0)) {
                IFX_REG_W32_MASK(1, 0, MBOX_IGU1_IER);
                napi_schedule(&g_ptm_priv_data.itf[0].napi);
#if defined(ENABLE_TMP_DBG) && ENABLE_TMP_DBG
                {
                    volatile struct rx_descriptor *desc = &WAN_RX_DESC_BASE[g_ptm_priv_data.itf[0].rx_desc_pos];

                    if ( desc->own ) {  //  PP32 hold
                        err("invalid interrupt");
                    }
                }
#endif
            }
	   if (isr & BIT(16)) {
                IFX_REG_W32_MASK(1 << 16, 0, MBOX_IGU1_IER);
                tasklet_hi_schedule(&g_swap_desc_tasklet);
            }
	    if (isr & BIT(17)) {
                IFX_REG_W32_MASK(1 << 17, 0, MBOX_IGU1_IER);
                netif_wake_queue(g_net_dev[0]);
        	}

    return IRQ_HANDLED;
}
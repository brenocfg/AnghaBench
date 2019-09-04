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
struct qcom_slim_ctrl {scalar_t__ base; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_NONE ; 
 int MGR_INT_RX_MSG_RCVD ; 
 scalar_t__ MGR_INT_STAT ; 
 int MGR_INT_TX_MSG_SENT ; 
 int MGR_INT_TX_NACKED_2 ; 
 int qcom_slim_handle_rx_irq (struct qcom_slim_ctrl*,int) ; 
 int qcom_slim_handle_tx_irq (struct qcom_slim_ctrl*,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static irqreturn_t qcom_slim_interrupt(int irq, void *d)
{
	struct qcom_slim_ctrl *ctrl = d;
	u32 stat = readl_relaxed(ctrl->base + MGR_INT_STAT);
	int ret = IRQ_NONE;

	if (stat & MGR_INT_TX_MSG_SENT || stat & MGR_INT_TX_NACKED_2)
		ret = qcom_slim_handle_tx_irq(ctrl, stat);

	if (stat & MGR_INT_RX_MSG_RCVD)
		ret = qcom_slim_handle_rx_irq(ctrl, stat);

	return ret;
}
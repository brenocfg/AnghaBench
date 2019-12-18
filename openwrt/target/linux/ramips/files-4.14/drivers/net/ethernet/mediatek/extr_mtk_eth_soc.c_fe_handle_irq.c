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
struct fe_priv {int /*<<< orphan*/  rx_napi; TYPE_1__* soc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int rx_int; int tx_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_REG_FE_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe_int_disable (int) ; 
 int fe_reg_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_reg_w32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct fe_priv* netdev_priv (void*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t fe_handle_irq(int irq, void *dev)
{
	struct fe_priv *priv = netdev_priv(dev);
	u32 status, int_mask;

	status = fe_reg_r32(FE_REG_FE_INT_STATUS);

	if (unlikely(!status))
		return IRQ_NONE;

	int_mask = (priv->soc->rx_int | priv->soc->tx_int);
	if (likely(status & int_mask)) {
		if (likely(napi_schedule_prep(&priv->rx_napi))) {
			fe_int_disable(int_mask);
			__napi_schedule(&priv->rx_napi);
		}
	} else {
		fe_reg_w32(status, FE_REG_FE_INT_STATUS);
	}

	return IRQ_HANDLED;
}
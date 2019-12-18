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
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  irq; } ;
struct fe_priv {TYPE_1__* soc; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int tx_int; int rx_int; scalar_t__ (* fwd_config ) (struct fe_priv*) ;int /*<<< orphan*/  (* set_mac ) (struct fe_priv*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t FE_REG_DLY_INT_CFG ; 
 size_t FE_REG_FE_DMA_VID_BASE ; 
 size_t FE_REG_FE_RST_GL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  fe_handle_irq ; 
 int /*<<< orphan*/  fe_hw_set_macaddr (struct fe_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_int_disable (int) ; 
 scalar_t__* fe_reg_table ; 
 int /*<<< orphan*/  fe_reg_w32 (int,size_t) ; 
 int /*<<< orphan*/  fe_w32 (int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct fe_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct fe_priv*) ; 

__attribute__((used)) static int fe_hw_init(struct net_device *dev)
{
	struct fe_priv *priv = netdev_priv(dev);
	int i, err;

	err = devm_request_irq(priv->dev, dev->irq, fe_handle_irq, 0,
			       dev_name(priv->dev), dev);
	if (err)
		return err;

	if (priv->soc->set_mac)
		priv->soc->set_mac(priv, dev->dev_addr);
	else
		fe_hw_set_macaddr(priv, dev->dev_addr);

	/* disable delay interrupt */
	fe_reg_w32(0, FE_REG_DLY_INT_CFG);

	fe_int_disable(priv->soc->tx_int | priv->soc->rx_int);

	/* frame engine will push VLAN tag regarding to VIDX feild in Tx desc */
	if (fe_reg_table[FE_REG_FE_DMA_VID_BASE])
		for (i = 0; i < 16; i += 2)
			fe_w32(((i + 1) << 16) + i,
			       fe_reg_table[FE_REG_FE_DMA_VID_BASE] +
			       (i * 2));

	if (priv->soc->fwd_config(priv))
		netdev_err(dev, "unable to get clock\n");

	if (fe_reg_table[FE_REG_FE_RST_GL]) {
		fe_reg_w32(1, FE_REG_FE_RST_GL);
		fe_reg_w32(0, FE_REG_FE_RST_GL);
	}

	return 0;
}
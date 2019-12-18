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
struct lpass_variant {int i2s_ports; int irq_ports; int rdma_channels; int wrdma_channels; scalar_t__ wrdma_channel_start; } ;
struct lpass_data {struct lpass_variant* variant; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int LPAIF_I2SCTL_REG (struct lpass_variant*,int) ; 
 unsigned int LPAIF_IRQEN_REG (struct lpass_variant*,int) ; 
 unsigned int LPAIF_IRQSTAT_REG (struct lpass_variant*,int) ; 
 unsigned int LPAIF_RDMABASE_REG (struct lpass_variant*,int) ; 
 unsigned int LPAIF_RDMABUFF_REG (struct lpass_variant*,int) ; 
 unsigned int LPAIF_RDMACTL_REG (struct lpass_variant*,int) ; 
 unsigned int LPAIF_RDMACURR_REG (struct lpass_variant*,int) ; 
 unsigned int LPAIF_RDMAPER_REG (struct lpass_variant*,int) ; 
 unsigned int LPAIF_WRDMABASE_REG (struct lpass_variant*,scalar_t__) ; 
 unsigned int LPAIF_WRDMABUFF_REG (struct lpass_variant*,scalar_t__) ; 
 unsigned int LPAIF_WRDMACTL_REG (struct lpass_variant*,scalar_t__) ; 
 unsigned int LPAIF_WRDMACURR_REG (struct lpass_variant*,scalar_t__) ; 
 unsigned int LPAIF_WRDMAPER_REG (struct lpass_variant*,scalar_t__) ; 
 struct lpass_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static bool lpass_cpu_regmap_readable(struct device *dev, unsigned int reg)
{
	struct lpass_data *drvdata = dev_get_drvdata(dev);
	struct lpass_variant *v = drvdata->variant;
	int i;

	for (i = 0; i < v->i2s_ports; ++i)
		if (reg == LPAIF_I2SCTL_REG(v, i))
			return true;

	for (i = 0; i < v->irq_ports; ++i) {
		if (reg == LPAIF_IRQEN_REG(v, i))
			return true;
		if (reg == LPAIF_IRQSTAT_REG(v, i))
			return true;
	}

	for (i = 0; i < v->rdma_channels; ++i) {
		if (reg == LPAIF_RDMACTL_REG(v, i))
			return true;
		if (reg == LPAIF_RDMABASE_REG(v, i))
			return true;
		if (reg == LPAIF_RDMABUFF_REG(v, i))
			return true;
		if (reg == LPAIF_RDMACURR_REG(v, i))
			return true;
		if (reg == LPAIF_RDMAPER_REG(v, i))
			return true;
	}

	for (i = 0; i < v->wrdma_channels; ++i) {
		if (reg == LPAIF_WRDMACTL_REG(v, i + v->wrdma_channel_start))
			return true;
		if (reg == LPAIF_WRDMABASE_REG(v, i + v->wrdma_channel_start))
			return true;
		if (reg == LPAIF_WRDMABUFF_REG(v, i + v->wrdma_channel_start))
			return true;
		if (reg == LPAIF_WRDMACURR_REG(v, i + v->wrdma_channel_start))
			return true;
		if (reg == LPAIF_WRDMAPER_REG(v, i + v->wrdma_channel_start))
			return true;
	}

	return false;
}
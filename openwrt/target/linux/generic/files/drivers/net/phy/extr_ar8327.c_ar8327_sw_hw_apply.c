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
struct switch_dev {int dummy; } ;
struct ar8xxx_priv {struct ar8327_data* chip_data; } ;
struct ar8327_data {scalar_t__* eee; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8327_EEE_CTRL_DISABLE_PHY (int) ; 
 int /*<<< orphan*/  AR8327_REG_EEE_CTRL ; 
 int AR8XXX_NUM_PHYS ; 
 int /*<<< orphan*/  ar8xxx_reg_clear (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_reg_set (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ar8xxx_sw_hw_apply (struct switch_dev*) ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

__attribute__((used)) static int
ar8327_sw_hw_apply(struct switch_dev *dev)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	const struct ar8327_data *data = priv->chip_data;
	int ret, i;

	ret = ar8xxx_sw_hw_apply(dev);
	if (ret)
		return ret;

	for (i=0; i < AR8XXX_NUM_PHYS; i++) {
		if (data->eee[i])
			ar8xxx_reg_clear(priv, AR8327_REG_EEE_CTRL,
			       AR8327_EEE_CTRL_DISABLE_PHY(i));
		else
			ar8xxx_reg_set(priv, AR8327_REG_EEE_CTRL,
			       AR8327_EEE_CTRL_DISABLE_PHY(i));
	}

	return 0;
}
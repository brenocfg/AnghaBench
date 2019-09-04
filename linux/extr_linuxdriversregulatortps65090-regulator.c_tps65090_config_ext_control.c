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
struct tps65090_regulator {TYPE_2__* dev; TYPE_1__* desc; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_3__ {unsigned int enable_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,unsigned int) ; 
 int tps65090_clr_bits (struct device*,unsigned int,int) ; 
 int tps65090_set_bits (struct device*,unsigned int,int) ; 

__attribute__((used)) static int tps65090_config_ext_control(
	struct tps65090_regulator *ri, bool enable)
{
	int ret;
	struct device *parent = ri->dev->parent;
	unsigned int reg_en_reg = ri->desc->enable_reg;

	if (enable)
		ret = tps65090_set_bits(parent, reg_en_reg, 1);
	else
		ret =  tps65090_clr_bits(parent, reg_en_reg, 1);
	if (ret < 0)
		dev_err(ri->dev, "Error in updating reg 0x%x\n", reg_en_reg);
	return ret;
}
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
struct rt9455_info {int voreg; int /*<<< orphan*/ * regmap_fields; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 size_t F_BATD_EN ; 
 size_t F_CHMIVRIM ; 
 int /*<<< orphan*/  F_IAICR ; 
 size_t F_IAICR_INT ; 
 int /*<<< orphan*/  F_ICHRG ; 
 int /*<<< orphan*/  F_IEOC_PERCENTAGE ; 
 int /*<<< orphan*/  F_MIVR ; 
 size_t F_TE ; 
 size_t F_TE_SHDN_EN ; 
 size_t F_TMR_EN ; 
 int /*<<< orphan*/  F_VMREG ; 
 int /*<<< orphan*/  F_VOREG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int* rt9455_iaicr_values ; 
 int* rt9455_ichrg_values ; 
 int* rt9455_ieoc_percentage_values ; 
 int* rt9455_mivr_values ; 
 int rt9455_register_reset (struct rt9455_info*) ; 
 int rt9455_set_field_val (struct rt9455_info*,int /*<<< orphan*/ ,int*,int,int) ; 
 int* rt9455_vmreg_values ; 
 int* rt9455_voreg_values ; 

__attribute__((used)) static int rt9455_hw_init(struct rt9455_info *info, u32 ichrg,
			  u32 ieoc_percentage,
			  u32 mivr, u32 iaicr)
{
	struct device *dev = &info->client->dev;
	int idx, ret;

	ret = rt9455_register_reset(info);
	if (ret) {
		dev_err(dev, "Power On Reset failed\n");
		return ret;
	}

	/* Set TE bit in order to enable end of charge detection */
	ret = regmap_field_write(info->regmap_fields[F_TE], 1);
	if (ret) {
		dev_err(dev, "Failed to set TE bit\n");
		return ret;
	}

	/* Set TE_SHDN_EN bit in order to enable end of charge detection */
	ret = regmap_field_write(info->regmap_fields[F_TE_SHDN_EN], 1);
	if (ret) {
		dev_err(dev, "Failed to set TE_SHDN_EN bit\n");
		return ret;
	}

	/*
	 * Set BATD_EN bit in order to enable battery detection
	 * when charging is done
	 */
	ret = regmap_field_write(info->regmap_fields[F_BATD_EN], 1);
	if (ret) {
		dev_err(dev, "Failed to set BATD_EN bit\n");
		return ret;
	}

	/*
	 * Disable Safety Timer. In charge mode, this timer terminates charging
	 * if no read or write via I2C is done within 32 minutes. This timer
	 * avoids overcharging the baterry when the OS is not loaded and the
	 * charger is connected to a power source.
	 * In boost mode, this timer triggers BST32SI interrupt if no read or
	 * write via I2C is done within 32 seconds.
	 * When the OS is loaded and the charger driver is inserted, it is used
	 * delayed_work, named max_charging_time_work, to avoid overcharging
	 * the battery.
	 */
	ret = regmap_field_write(info->regmap_fields[F_TMR_EN], 0x00);
	if (ret) {
		dev_err(dev, "Failed to disable Safety Timer\n");
		return ret;
	}

	/* Set ICHRG to value retrieved from device-specific data */
	ret = rt9455_set_field_val(info, F_ICHRG,
				   rt9455_ichrg_values,
				   ARRAY_SIZE(rt9455_ichrg_values), ichrg);
	if (ret) {
		dev_err(dev, "Failed to set ICHRG value\n");
		return ret;
	}

	/* Set IEOC Percentage to value retrieved from device-specific data */
	ret = rt9455_set_field_val(info, F_IEOC_PERCENTAGE,
				   rt9455_ieoc_percentage_values,
				   ARRAY_SIZE(rt9455_ieoc_percentage_values),
				   ieoc_percentage);
	if (ret) {
		dev_err(dev, "Failed to set IEOC Percentage value\n");
		return ret;
	}

	/* Set VOREG to value retrieved from device-specific data */
	ret = rt9455_set_field_val(info, F_VOREG,
				   rt9455_voreg_values,
				   ARRAY_SIZE(rt9455_voreg_values),
				   info->voreg);
	if (ret) {
		dev_err(dev, "Failed to set VOREG value\n");
		return ret;
	}

	/* Set VMREG value to maximum (4.45V). */
	idx = ARRAY_SIZE(rt9455_vmreg_values) - 1;
	ret = rt9455_set_field_val(info, F_VMREG,
				   rt9455_vmreg_values,
				   ARRAY_SIZE(rt9455_vmreg_values),
				   rt9455_vmreg_values[idx]);
	if (ret) {
		dev_err(dev, "Failed to set VMREG value\n");
		return ret;
	}

	/*
	 * Set MIVR to value retrieved from device-specific data.
	 * If no value is specified, default value for MIVR is 4.5V.
	 */
	if (mivr == -1)
		mivr = 4500000;

	ret = rt9455_set_field_val(info, F_MIVR,
				   rt9455_mivr_values,
				   ARRAY_SIZE(rt9455_mivr_values), mivr);
	if (ret) {
		dev_err(dev, "Failed to set MIVR value\n");
		return ret;
	}

	/*
	 * Set IAICR to value retrieved from device-specific data.
	 * If no value is specified, default value for IAICR is 500 mA.
	 */
	if (iaicr == -1)
		iaicr = 500000;

	ret = rt9455_set_field_val(info, F_IAICR,
				   rt9455_iaicr_values,
				   ARRAY_SIZE(rt9455_iaicr_values), iaicr);
	if (ret) {
		dev_err(dev, "Failed to set IAICR value\n");
		return ret;
	}

	/*
	 * Set IAICR_INT bit so that IAICR value is determined by IAICR bits
	 * and not by OTG pin.
	 */
	ret = regmap_field_write(info->regmap_fields[F_IAICR_INT], 0x01);
	if (ret) {
		dev_err(dev, "Failed to set IAICR_INT bit\n");
		return ret;
	}

	/*
	 * Disable CHMIVRI interrupt. Because the driver sets MIVR value,
	 * CHMIVRI is triggered, but there is no action to be taken by the
	 * driver when CHMIVRI is triggered.
	 */
	ret = regmap_field_write(info->regmap_fields[F_CHMIVRIM], 0x01);
	if (ret) {
		dev_err(dev, "Failed to mask CHMIVRI interrupt\n");
		return ret;
	}

	return 0;
}
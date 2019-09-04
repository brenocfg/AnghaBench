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
typedef  int /*<<< orphan*/  u32 ;
struct platform_device {int dummy; } ;
struct armada_thermal_priv {int /*<<< orphan*/  syscon; struct armada_thermal_data* data; } ;
struct armada_thermal_data {int /*<<< orphan*/  syscon_control0_off; int /*<<< orphan*/  syscon_control1_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL0_TSEN_TC_TRIM_MASK ; 
 int /*<<< orphan*/  CONTROL0_TSEN_TC_TRIM_VAL ; 
 int /*<<< orphan*/  CONTROL1_EXT_TSEN_HW_RESETn ; 
 int /*<<< orphan*/  CONTROL1_EXT_TSEN_SW_RESET ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armada380_init(struct platform_device *pdev,
			   struct armada_thermal_priv *priv)
{
	struct armada_thermal_data *data = priv->data;
	u32 reg;

	/* Disable the HW/SW reset */
	regmap_read(priv->syscon, data->syscon_control1_off, &reg);
	reg |= CONTROL1_EXT_TSEN_HW_RESETn;
	reg &= ~CONTROL1_EXT_TSEN_SW_RESET;
	regmap_write(priv->syscon, data->syscon_control1_off, reg);

	/* Set Tsen Tc Trim to correct default value (errata #132698) */
	regmap_read(priv->syscon, data->syscon_control0_off, &reg);
	reg &= ~CONTROL0_TSEN_TC_TRIM_MASK;
	reg |= CONTROL0_TSEN_TC_TRIM_VAL;
	regmap_write(priv->syscon, data->syscon_control0_off, reg);
}
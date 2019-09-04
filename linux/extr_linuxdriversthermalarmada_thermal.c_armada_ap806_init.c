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
struct platform_device {int dummy; } ;
struct armada_thermal_priv {int /*<<< orphan*/  syscon; struct armada_thermal_data* data; } ;
struct armada_thermal_data {int /*<<< orphan*/  syscon_control0_off; } ;

/* Variables and functions */
 int CONTROL0_TSEN_AVG_BYPASS ; 
 int CONTROL0_TSEN_ENABLE ; 
 int CONTROL0_TSEN_OSR_MAX ; 
 int CONTROL0_TSEN_OSR_SHIFT ; 
 int CONTROL0_TSEN_RESET ; 
 int CONTROL0_TSEN_START ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void armada_ap806_init(struct platform_device *pdev,
			      struct armada_thermal_priv *priv)
{
	struct armada_thermal_data *data = priv->data;
	u32 reg;

	regmap_read(priv->syscon, data->syscon_control0_off, &reg);
	reg &= ~CONTROL0_TSEN_RESET;
	reg |= CONTROL0_TSEN_START | CONTROL0_TSEN_ENABLE;

	/* Sample every ~2ms */
	reg |= CONTROL0_TSEN_OSR_MAX << CONTROL0_TSEN_OSR_SHIFT;

	/* Enable average (2 samples by default) */
	reg &= ~CONTROL0_TSEN_AVG_BYPASS;

	regmap_write(priv->syscon, data->syscon_control0_off, reg);
}
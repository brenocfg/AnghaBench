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
struct dove_thermal_priv {int /*<<< orphan*/  sensor; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int DOVE_THERMAL_TEMP_MASK ; 
 int EIO ; 
 int PMU_TDC0_AVG_NUM_MASK ; 
 int PMU_TDC0_AVG_NUM_OFFS ; 
 int PMU_TDC0_REF_CAL_CNT_MASK ; 
 int PMU_TDC0_REF_CAL_CNT_OFFS ; 
 int PMU_TDC0_SEL_VCAL_MASK ; 
 int PMU_TDC0_SEL_VCAL_OFFS ; 
 int PMU_TDC0_SW_RST_MASK ; 
 int PMU_TM_DISABLE_MASK ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dove_init_sensor(const struct dove_thermal_priv *priv)
{
	u32 reg;
	u32 i;

	/* Configure the Diode Control Register #0 */
	reg = readl_relaxed(priv->control);

	/* Use average of 2 */
	reg &= ~PMU_TDC0_AVG_NUM_MASK;
	reg |= (0x1 << PMU_TDC0_AVG_NUM_OFFS);

	/* Reference calibration value */
	reg &= ~PMU_TDC0_REF_CAL_CNT_MASK;
	reg |= (0x0F1 << PMU_TDC0_REF_CAL_CNT_OFFS);

	/* Set the high level reference for calibration */
	reg &= ~PMU_TDC0_SEL_VCAL_MASK;
	reg |= (0x2 << PMU_TDC0_SEL_VCAL_OFFS);
	writel(reg, priv->control);

	/* Reset the sensor */
	reg = readl_relaxed(priv->control);
	writel((reg | PMU_TDC0_SW_RST_MASK), priv->control);
	writel(reg, priv->control);

	/* Enable the sensor */
	reg = readl_relaxed(priv->sensor);
	reg &= ~PMU_TM_DISABLE_MASK;
	writel(reg, priv->sensor);

	/* Poll the sensor for the first reading */
	for (i = 0; i < 1000000; i++) {
		reg = readl_relaxed(priv->sensor);
		if (reg & DOVE_THERMAL_TEMP_MASK)
			break;
	}

	if (i == 1000000)
		return -EIO;

	return 0;
}
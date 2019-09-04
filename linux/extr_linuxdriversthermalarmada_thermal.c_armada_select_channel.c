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
struct armada_thermal_priv {int current_channel; int /*<<< orphan*/  dev; int /*<<< orphan*/  syscon; struct armada_thermal_data* data; } ;
struct armada_thermal_data {int cpu_nr; int /*<<< orphan*/  syscon_control0_off; } ;

/* Variables and functions */
 int CONTROL0_TSEN_CHAN_MASK ; 
 int CONTROL0_TSEN_CHAN_SHIFT ; 
 int CONTROL0_TSEN_MODE_EXTERNAL ; 
 int CONTROL0_TSEN_MODE_MASK ; 
 int CONTROL0_TSEN_MODE_SHIFT ; 
 int CONTROL0_TSEN_START ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ armada_wait_sensor_validity (struct armada_thermal_priv*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int armada_select_channel(struct armada_thermal_priv *priv, int channel)
{
	struct armada_thermal_data *data = priv->data;
	u32 ctrl0;

	if (channel < 0 || channel > priv->data->cpu_nr)
		return -EINVAL;

	if (priv->current_channel == channel)
		return 0;

	/* Stop the measurements */
	regmap_read(priv->syscon, data->syscon_control0_off, &ctrl0);
	ctrl0 &= ~CONTROL0_TSEN_START;
	regmap_write(priv->syscon, data->syscon_control0_off, ctrl0);

	/* Reset the mode, internal sensor will be automatically selected */
	ctrl0 &= ~(CONTROL0_TSEN_MODE_MASK << CONTROL0_TSEN_MODE_SHIFT);

	/* Other channels are external and should be selected accordingly */
	if (channel) {
		/* Change the mode to external */
		ctrl0 |= CONTROL0_TSEN_MODE_EXTERNAL <<
			 CONTROL0_TSEN_MODE_SHIFT;
		/* Select the sensor */
		ctrl0 &= ~(CONTROL0_TSEN_CHAN_MASK << CONTROL0_TSEN_CHAN_SHIFT);
		ctrl0 |= (channel - 1) << CONTROL0_TSEN_CHAN_SHIFT;
	}

	/* Actually set the mode/channel */
	regmap_write(priv->syscon, data->syscon_control0_off, ctrl0);
	priv->current_channel = channel;

	/* Re-start the measurements */
	ctrl0 |= CONTROL0_TSEN_START;
	regmap_write(priv->syscon, data->syscon_control0_off, ctrl0);

	/*
	 * The IP has a latency of ~15ms, so after updating the selected source,
	 * we must absolutely wait for the sensor validity bit to ensure we read
	 * actual data.
	 */
	if (armada_wait_sensor_validity(priv)) {
		dev_err(priv->dev,
			"Temperature sensor reading not valid\n");
		return -EIO;
	}

	return 0;
}
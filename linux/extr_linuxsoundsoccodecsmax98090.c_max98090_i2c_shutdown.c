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
struct max98090_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M98090_REG_DEVICE_SHUTDOWN ; 
 int /*<<< orphan*/  M98090_REG_LEVEL_CONTROL ; 
 int M98090_VSENN_MASK ; 
 struct max98090_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void max98090_i2c_shutdown(struct i2c_client *i2c)
{
	struct max98090_priv *max98090 = dev_get_drvdata(&i2c->dev);

	/*
	 * Enable volume smoothing, disable zero cross.  This will cause
	 * a quick 40ms ramp to mute on shutdown.
	 */
	regmap_write(max98090->regmap,
		M98090_REG_LEVEL_CONTROL, M98090_VSENN_MASK);
	regmap_write(max98090->regmap,
		M98090_REG_DEVICE_SHUTDOWN, 0x00);
	msleep(40);
}
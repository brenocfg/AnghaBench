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
struct tlv320dac33_priv {scalar_t__ power_gpio; int /*<<< orphan*/  component; int /*<<< orphan*/  chip_power; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dac33_hard_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 struct tlv320dac33_priv* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dac33_i2c_remove(struct i2c_client *client)
{
	struct tlv320dac33_priv *dac33 = i2c_get_clientdata(client);

	if (unlikely(dac33->chip_power))
		dac33_hard_power(dac33->component, 0);

	if (dac33->power_gpio >= 0)
		gpio_free(dac33->power_gpio);

	return 0;
}
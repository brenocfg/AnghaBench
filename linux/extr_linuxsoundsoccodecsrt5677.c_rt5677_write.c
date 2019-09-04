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
struct rt5677_priv {int /*<<< orphan*/  regmap_physical; int /*<<< orphan*/  dsp_pri_lock; scalar_t__ is_dsp_mode; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 unsigned int RT5677_PRIV_DATA ; 
 unsigned int RT5677_PRIV_INDEX ; 
 struct rt5677_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rt5677_dsp_mode_i2c_write (struct rt5677_priv*,unsigned int,unsigned int) ; 

__attribute__((used)) static int rt5677_write(void *context, unsigned int reg, unsigned int val)
{
	struct i2c_client *client = context;
	struct rt5677_priv *rt5677 = i2c_get_clientdata(client);

	if (rt5677->is_dsp_mode) {
		if (reg > 0xff) {
			mutex_lock(&rt5677->dsp_pri_lock);
			rt5677_dsp_mode_i2c_write(rt5677, RT5677_PRIV_INDEX,
				reg & 0xff);
			rt5677_dsp_mode_i2c_write(rt5677, RT5677_PRIV_DATA,
				val);
			mutex_unlock(&rt5677->dsp_pri_lock);
		} else {
			rt5677_dsp_mode_i2c_write(rt5677, reg, val);
		}
	} else {
		regmap_write(rt5677->regmap_physical, reg, val);
	}

	return 0;
}
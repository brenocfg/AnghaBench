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
struct wm2000_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct wm2000_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int wm2000_write(struct i2c_client *i2c, unsigned int reg,
			unsigned int value)
{
	struct wm2000_priv *wm2000 = i2c_get_clientdata(i2c);
	return regmap_write(wm2000->regmap, reg, value);
}
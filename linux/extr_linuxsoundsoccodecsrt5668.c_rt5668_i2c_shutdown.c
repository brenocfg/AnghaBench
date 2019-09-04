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
struct rt5668_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct rt5668_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  rt5668_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5668_i2c_shutdown(struct i2c_client *client)
{
	struct rt5668_priv *rt5668 = i2c_get_clientdata(client);

	rt5668_reset(rt5668->regmap);
}
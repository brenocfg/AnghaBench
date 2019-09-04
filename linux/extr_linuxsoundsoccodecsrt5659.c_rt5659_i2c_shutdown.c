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
struct rt5659_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5659_RESET ; 
 struct rt5659_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5659_i2c_shutdown(struct i2c_client *client)
{
	struct rt5659_priv *rt5659 = i2c_get_clientdata(client);

	regmap_write(rt5659->regmap, RT5659_RESET, 0);
}
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
struct rt1305_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct rt1305_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  rt1305_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt1305_i2c_shutdown(struct i2c_client *client)
{
	struct rt1305_priv *rt1305 = i2c_get_clientdata(client);

	rt1305_reset(rt1305->regmap);
}
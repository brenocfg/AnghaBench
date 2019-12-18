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
struct rt5645_priv {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5645_CBJ_BST1_EN ; 
 int /*<<< orphan*/  RT5645_CBJ_MN_JD ; 
 int /*<<< orphan*/  RT5645_GEN_CTRL3 ; 
 int /*<<< orphan*/  RT5645_IN1_CTRL1 ; 
 int /*<<< orphan*/  RT5645_IN1_CTRL2 ; 
 int /*<<< orphan*/  RT5645_RESET ; 
 int /*<<< orphan*/  RT5645_RING2_SLEEVE_GND ; 
 struct rt5645_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt5645_i2c_shutdown(struct i2c_client *i2c)
{
	struct rt5645_priv *rt5645 = i2c_get_clientdata(i2c);

	regmap_update_bits(rt5645->regmap, RT5645_GEN_CTRL3,
		RT5645_RING2_SLEEVE_GND, RT5645_RING2_SLEEVE_GND);
	regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL2, RT5645_CBJ_MN_JD,
		RT5645_CBJ_MN_JD);
	regmap_update_bits(rt5645->regmap, RT5645_IN1_CTRL1, RT5645_CBJ_BST1_EN,
		0);
	msleep(20);
	regmap_write(rt5645->regmap, RT5645_RESET, 0);
}
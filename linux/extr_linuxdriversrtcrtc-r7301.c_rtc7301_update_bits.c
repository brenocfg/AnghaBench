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
typedef  int /*<<< orphan*/  u8 ;
struct rtc7301_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_get_reg_stride (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc7301_update_bits(struct rtc7301_priv *priv, unsigned int reg,
				u8 mask, u8 val)
{
	int reg_stride = regmap_get_reg_stride(priv->regmap);

	regmap_update_bits(priv->regmap, reg_stride * reg, mask, val);
}
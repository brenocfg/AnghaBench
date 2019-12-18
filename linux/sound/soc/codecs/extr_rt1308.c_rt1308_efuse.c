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
struct rt1308_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT1308_EFUSE_1 ; 
 int /*<<< orphan*/  RT1308_POWER_STATUS ; 
 int /*<<< orphan*/  RT1308_PVDD_OFFSET_CTL ; 
 int /*<<< orphan*/  RT1308_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt1308_efuse(struct rt1308_priv *rt1308)
{
	regmap_write(rt1308->regmap, RT1308_RESET, 0);

	regmap_write(rt1308->regmap, RT1308_POWER_STATUS, 0x01800000);
	msleep(100);
	regmap_write(rt1308->regmap, RT1308_EFUSE_1, 0x44fe0f00);
	msleep(20);
	regmap_write(rt1308->regmap, RT1308_PVDD_OFFSET_CTL, 0x10000000);
}
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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAU8540_REG_SW_RESET ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nau8540_reset_chip(struct regmap *regmap)
{
	regmap_write(regmap, NAU8540_REG_SW_RESET, 0x00);
	regmap_write(regmap, NAU8540_REG_SW_RESET, 0x00);
}
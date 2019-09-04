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
struct rv3028_data {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 long DIV_ROUND_CLOSEST (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFFSET_STEP_PPT ; 
 int /*<<< orphan*/  RV3028_BACKUP ; 
 int /*<<< orphan*/  RV3028_OFFSET ; 
 int clamp (long,long,long) ; 
 struct rv3028_data* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int rv3028_set_offset(struct device *dev, long offset)
{
	struct rv3028_data *rv3028 = dev_get_drvdata(dev);
	int ret;

	offset = clamp(offset, -244141L, 243187L) * 1000;
	offset = DIV_ROUND_CLOSEST(offset, OFFSET_STEP_PPT);

	ret = regmap_write(rv3028->regmap, RV3028_OFFSET, offset >> 1);
	if (ret < 0)
		return ret;

	return regmap_update_bits(rv3028->regmap, RV3028_BACKUP, BIT(7),
				  offset << 7);
}
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
struct reset_controller_dev {int dummy; } ;
struct regmap {int dummy; } ;
struct hi6220_reset_data {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned long) ; 
 int /*<<< orphan*/  SC_MEDIA_RSTDIS ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hi6220_reset_data* to_reset_data (struct reset_controller_dev*) ; 

__attribute__((used)) static int hi6220_media_deassert(struct reset_controller_dev *rc_dev,
				 unsigned long idx)
{
	struct hi6220_reset_data *data = to_reset_data(rc_dev);
	struct regmap *regmap = data->regmap;

	return regmap_write(regmap, SC_MEDIA_RSTDIS, BIT(idx));
}
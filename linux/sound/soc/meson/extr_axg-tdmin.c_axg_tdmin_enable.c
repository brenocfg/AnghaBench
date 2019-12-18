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
 int /*<<< orphan*/  TDMIN_CTRL ; 
 int TDMIN_CTRL_ENABLE ; 
 int TDMIN_CTRL_RST_IN ; 
 int TDMIN_CTRL_RST_OUT ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void axg_tdmin_enable(struct regmap *map)
{
	/* Apply both reset */
	regmap_update_bits(map, TDMIN_CTRL,
			   TDMIN_CTRL_RST_OUT | TDMIN_CTRL_RST_IN, 0);

	/* Clear out reset before in reset */
	regmap_update_bits(map, TDMIN_CTRL,
			   TDMIN_CTRL_RST_OUT, TDMIN_CTRL_RST_OUT);
	regmap_update_bits(map, TDMIN_CTRL,
			   TDMIN_CTRL_RST_IN,  TDMIN_CTRL_RST_IN);

	/* Actually enable tdmin */
	regmap_update_bits(map, TDMIN_CTRL,
			   TDMIN_CTRL_ENABLE, TDMIN_CTRL_ENABLE);
}
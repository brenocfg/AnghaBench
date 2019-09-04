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
typedef  scalar_t__ const u16 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int CS43130_DC_THRESHOLD ; 
 int /*<<< orphan*/ * hv_seq ; 
 int /*<<< orphan*/  regmap_multi_reg_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs43130_set_hv(struct regmap *regmap, u16 hpload_dc,
			  const u16 *dc_threshold)
{
	int i;

	for (i = 0; i < CS43130_DC_THRESHOLD; i++) {
		if (hpload_dc <= dc_threshold[i])
			break;
	}

	regmap_multi_reg_write(regmap, hv_seq[i], ARRAY_SIZE(hv_seq[i]));

	return 0;
}
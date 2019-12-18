#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* out_vol_limit; } ;
struct arizona {TYPE_1__ pdata; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ ARIZONA_DAC_VOLUME_LIMIT_1L ; 
 int /*<<< orphan*/  ARIZONA_OUT1L_VOL_LIM_MASK ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

int arizona_init_vol_limit(struct arizona *arizona)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(arizona->pdata.out_vol_limit); ++i) {
		if (arizona->pdata.out_vol_limit[i])
			regmap_update_bits(arizona->regmap,
					   ARIZONA_DAC_VOLUME_LIMIT_1L + i * 4,
					   ARIZONA_OUT1L_VOL_LIM_MASK,
					   arizona->pdata.out_vol_limit[i]);
	}

	return 0;
}
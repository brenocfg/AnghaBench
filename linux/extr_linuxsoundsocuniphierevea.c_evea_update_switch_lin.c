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
struct evea_priv {scalar_t__ switch_lin; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AADCPOW (int) ; 
 int AADCPOW_AADC_POWD ; 
 int /*<<< orphan*/  ALINEPOW ; 
 int ALINEPOW_LIN1_POWD ; 
 int ALINEPOW_LIN2_POWD ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int evea_update_switch_lin(struct evea_priv *evea)
{
	struct regmap *map = evea->regmap;

	if (evea->switch_lin) {
		regmap_update_bits(map, ALINEPOW,
				   ALINEPOW_LIN2_POWD | ALINEPOW_LIN1_POWD,
				   ALINEPOW_LIN2_POWD | ALINEPOW_LIN1_POWD);

		regmap_update_bits(map, AADCPOW(0), AADCPOW_AADC_POWD,
				   AADCPOW_AADC_POWD);
		regmap_update_bits(map, AADCPOW(1), AADCPOW_AADC_POWD,
				   AADCPOW_AADC_POWD);
	} else {
		regmap_update_bits(map, AADCPOW(0), AADCPOW_AADC_POWD, 0);
		regmap_update_bits(map, AADCPOW(1), AADCPOW_AADC_POWD, 0);

		regmap_update_bits(map, ALINEPOW,
				   ALINEPOW_LIN2_POWD | ALINEPOW_LIN1_POWD, 0);
	}

	return 0;
}
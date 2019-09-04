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
struct tps65217_charger {int /*<<< orphan*/  dev; int /*<<< orphan*/  tps; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS65217_CHGCONFIG1_NTC_TYPE ; 
 int /*<<< orphan*/  TPS65217_PROTECT_NONE ; 
 int /*<<< orphan*/  TPS65217_REG_CHGCONFIG1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int tps65217_clear_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65217_config_charger(struct tps65217_charger *charger)
{
	int ret;

	/*
	 * tps65217 rev. G, p. 31 (see p. 32 for NTC schematic)
	 *
	 * The device can be configured to support a 100k NTC (B = 3960) by
	 * setting the the NTC_TYPE bit in register CHGCONFIG1 to 1. However it
	 * is not recommended to do so. In sleep mode, the charger continues
	 * charging the battery, but all register values are reset to default
	 * values. Therefore, the charger would get the wrong temperature
	 * information. If 100k NTC setting is required, please contact the
	 * factory.
	 *
	 * ATTENTION, conflicting information, from p. 46
	 *
	 * NTC TYPE (for battery temperature measurement)
	 *   0 – 100k (curve 1, B = 3960)
	 *   1 – 10k  (curve 2, B = 3480) (default on reset)
	 *
	 */
	ret = tps65217_clear_bits(charger->tps, TPS65217_REG_CHGCONFIG1,
				  TPS65217_CHGCONFIG1_NTC_TYPE,
				  TPS65217_PROTECT_NONE);
	if (ret) {
		dev_err(charger->dev,
			"failed to set 100k NTC setting: %d\n", ret);
		return ret;
	}

	return 0;
}
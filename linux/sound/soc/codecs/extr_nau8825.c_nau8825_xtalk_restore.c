#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nau8825 {int xtalk_baktab_initialized; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {scalar_t__ reg; int def; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int NAU8825_HPR_VOL_MASK ; 
 scalar_t__ NAU8825_REG_HSVOL_CTRL ; 
 int /*<<< orphan*/  nau8825_hpvol_ramp (struct nau8825*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* nau8825_xtalk_baktab ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void nau8825_xtalk_restore(struct nau8825 *nau8825, bool cause_cancel)
{
	int i, volume;

	if (!nau8825->xtalk_baktab_initialized)
		return;

	/* Restore register values from backup table; When the driver restores
	 * the headphone volume in XTALK_DONE state, it needs recover to
	 * original level gradually with 3dB per step for less pop noise.
	 * Otherwise, the restore should do ASAP.
	 */
	for (i = 0; i < ARRAY_SIZE(nau8825_xtalk_baktab); i++) {
		if (!cause_cancel && nau8825_xtalk_baktab[i].reg ==
			NAU8825_REG_HSVOL_CTRL) {
			/* Ramping up the volume change to reduce pop noise */
			volume = nau8825_xtalk_baktab[i].def &
				NAU8825_HPR_VOL_MASK;
			nau8825_hpvol_ramp(nau8825, 0, volume, 3);
			continue;
		}
		regmap_write(nau8825->regmap, nau8825_xtalk_baktab[i].reg,
				nau8825_xtalk_baktab[i].def);
	}

	nau8825->xtalk_baktab_initialized = false;
}
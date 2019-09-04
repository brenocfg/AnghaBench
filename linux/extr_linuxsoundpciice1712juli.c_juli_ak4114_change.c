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
struct snd_ice1712 {int /*<<< orphan*/  akm; scalar_t__ (* is_spdif_master ) (struct snd_ice1712*) ;} ;
struct ak4114 {struct snd_ice1712* change_callback_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  juli_akm_set_rate_val (int /*<<< orphan*/ ,int) ; 
 int snd_ak4114_external_rate (struct ak4114*) ; 
 scalar_t__ stub1 (struct snd_ice1712*) ; 

__attribute__((used)) static void juli_ak4114_change(struct ak4114 *ak4114, unsigned char c0,
			       unsigned char c1)
{
	struct snd_ice1712 *ice = ak4114->change_callback_private;
	int rate;
	if (ice->is_spdif_master(ice) && c1) {
		/* only for SPDIF master mode, rate was changed */
		rate = snd_ak4114_external_rate(ak4114);
		/* dev_dbg(ice->card->dev, "ak4114 - input rate changed to %d\n",
				rate); */
		juli_akm_set_rate_val(ice->akm, rate);
	}
}
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
struct snd_ice1712 {int /*<<< orphan*/  akm; } ;
struct ak4113 {struct snd_ice1712* change_callback_private; } ;

/* Variables and functions */
 scalar_t__ EXT_SPDIF_TYPE ; 
 int /*<<< orphan*/  qtet_akm_set_rate_val (int /*<<< orphan*/ ,int) ; 
 scalar_t__ qtet_get_spdif_master_type (struct snd_ice1712*) ; 
 int snd_ak4113_external_rate (struct ak4113*) ; 

__attribute__((used)) static void qtet_ak4113_change(struct ak4113 *ak4113, unsigned char c0,
		unsigned char c1)
{
	struct snd_ice1712 *ice = ak4113->change_callback_private;
	int rate;
	if ((qtet_get_spdif_master_type(ice) == EXT_SPDIF_TYPE) &&
			c1) {
		/* only for SPDIF master mode, rate was changed */
		rate = snd_ak4113_external_rate(ak4113);
		/* dev_dbg(ice->card->dev, "ak4113 - input rate changed to %d\n",
		   rate); */
		qtet_akm_set_rate_val(ice->akm, rate);
	}
}
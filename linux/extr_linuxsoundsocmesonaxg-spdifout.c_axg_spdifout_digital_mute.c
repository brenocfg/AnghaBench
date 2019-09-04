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
struct snd_soc_dai {int dummy; } ;
struct axg_spdifout {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPDIFOUT_CTRL0 ; 
 int /*<<< orphan*/  SPDIFOUT_CTRL0_VSET ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axg_spdifout* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int axg_spdifout_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct axg_spdifout *priv = snd_soc_dai_get_drvdata(dai);

	/* Use spdif valid bit to perform digital mute */
	regmap_update_bits(priv->map, SPDIFOUT_CTRL0, SPDIFOUT_CTRL0_VSET,
			   mute ? SPDIFOUT_CTRL0_VSET : 0);

	return 0;
}
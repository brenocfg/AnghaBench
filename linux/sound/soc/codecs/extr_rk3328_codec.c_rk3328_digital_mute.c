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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct rk3328_codec_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int HPOUTL_MUTE ; 
 int HPOUTL_MUTE_MASK ; 
 unsigned int HPOUTL_UNMUTE ; 
 unsigned int HPOUTR_MUTE ; 
 int HPOUTR_MUTE_MASK ; 
 unsigned int HPOUTR_UNMUTE ; 
 int /*<<< orphan*/  HPOUT_CTRL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct rk3328_codec_priv* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3328_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct rk3328_codec_priv *rk3328 =
		snd_soc_component_get_drvdata(dai->component);
	unsigned int val;

	if (mute)
		val = HPOUTL_MUTE | HPOUTR_MUTE;
	else
		val = HPOUTL_UNMUTE | HPOUTR_UNMUTE;

	regmap_update_bits(rk3328->regmap, HPOUT_CTRL,
			   HPOUTL_MUTE_MASK | HPOUTR_MUTE_MASK, val);

	return 0;
}
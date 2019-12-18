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
struct snd_soc_component {int dummy; } ;
struct adav80x {int rate; int /*<<< orphan*/  regmap; scalar_t__ deemph; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAV80X_DAC_CTRL2 ; 
 unsigned int ADAV80X_DAC_CTRL2_DEEMPH_32 ; 
 unsigned int ADAV80X_DAC_CTRL2_DEEMPH_44 ; 
 unsigned int ADAV80X_DAC_CTRL2_DEEMPH_48 ; 
 int /*<<< orphan*/  ADAV80X_DAC_CTRL2_DEEMPH_MASK ; 
 unsigned int ADAV80X_DAC_CTRL2_DEEMPH_NONE ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct adav80x* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adav80x_set_deemph(struct snd_soc_component *component)
{
	struct adav80x *adav80x = snd_soc_component_get_drvdata(component);
	unsigned int val;

	if (adav80x->deemph) {
		switch (adav80x->rate) {
		case 32000:
			val = ADAV80X_DAC_CTRL2_DEEMPH_32;
			break;
		case 44100:
			val = ADAV80X_DAC_CTRL2_DEEMPH_44;
			break;
		case 48000:
		case 64000:
		case 88200:
		case 96000:
			val = ADAV80X_DAC_CTRL2_DEEMPH_48;
			break;
		default:
			val = ADAV80X_DAC_CTRL2_DEEMPH_NONE;
			break;
		}
	} else {
		val = ADAV80X_DAC_CTRL2_DEEMPH_NONE;
	}

	return regmap_update_bits(adav80x->regmap, ADAV80X_DAC_CTRL2,
		ADAV80X_DAC_CTRL2_DEEMPH_MASK, val);
}
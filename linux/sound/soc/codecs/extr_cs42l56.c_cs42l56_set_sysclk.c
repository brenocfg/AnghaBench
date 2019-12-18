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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct cs42l56_private {unsigned int mclk; void* mclk_div2; void* mclk_prediv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS42L56_CLKCTL_1 ; 
#define  CS42L56_MCLK_11P2896MHZ 136 
#define  CS42L56_MCLK_12MHZ 135 
#define  CS42L56_MCLK_12P288MHZ 134 
#define  CS42L56_MCLK_22P5792MHZ 133 
#define  CS42L56_MCLK_24MHZ 132 
#define  CS42L56_MCLK_24P576MHZ 131 
#define  CS42L56_MCLK_5P6448MHZ 130 
#define  CS42L56_MCLK_6MHZ 129 
#define  CS42L56_MCLK_6P144MHZ 128 
 void* CS42L56_MCLK_DIV2 ; 
 int /*<<< orphan*/  CS42L56_MCLK_DIV2_MASK ; 
 void* CS42L56_MCLK_PREDIV ; 
 int /*<<< orphan*/  CS42L56_MCLK_PREDIV_MASK ; 
 int EINVAL ; 
 struct cs42l56_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int cs42l56_set_sysclk(struct snd_soc_dai *codec_dai,
			int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs42l56_private *cs42l56 = snd_soc_component_get_drvdata(component);

	switch (freq) {
	case CS42L56_MCLK_5P6448MHZ:
	case CS42L56_MCLK_6MHZ:
	case CS42L56_MCLK_6P144MHZ:
		cs42l56->mclk_div2 = 0;
		cs42l56->mclk_prediv = 0;
		break;
	case CS42L56_MCLK_11P2896MHZ:
	case CS42L56_MCLK_12MHZ:
	case CS42L56_MCLK_12P288MHZ:
		cs42l56->mclk_div2 = CS42L56_MCLK_DIV2;
		cs42l56->mclk_prediv = 0;
		break;
	case CS42L56_MCLK_22P5792MHZ:
	case CS42L56_MCLK_24MHZ:
	case CS42L56_MCLK_24P576MHZ:
		cs42l56->mclk_div2 = CS42L56_MCLK_DIV2;
		cs42l56->mclk_prediv = CS42L56_MCLK_PREDIV;
		break;
	default:
		return -EINVAL;
	}
	cs42l56->mclk = freq;

	snd_soc_component_update_bits(component, CS42L56_CLKCTL_1,
			    CS42L56_MCLK_PREDIV_MASK,
				cs42l56->mclk_prediv);
	snd_soc_component_update_bits(component, CS42L56_CLKCTL_1,
			    CS42L56_MCLK_DIV2_MASK,
				cs42l56->mclk_div2);

	return 0;
}
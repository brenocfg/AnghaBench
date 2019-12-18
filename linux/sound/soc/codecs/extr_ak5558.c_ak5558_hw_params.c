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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct ak5558_priv {int /*<<< orphan*/  slot_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK5558_02_CONTROL1 ; 
 int /*<<< orphan*/  AK5558_BITS ; 
 int /*<<< orphan*/  AK5558_DIF_24BIT_MODE ; 
 int /*<<< orphan*/  AK5558_DIF_32BIT_MODE ; 
 int EINVAL ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_physical_width (struct snd_pcm_hw_params*) ; 
 struct ak5558_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ak5558_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct ak5558_priv *ak5558 = snd_soc_component_get_drvdata(component);
	u8 bits;
	int pcm_width = max(params_physical_width(params), ak5558->slot_width);

	switch (pcm_width) {
	case 16:
		bits = AK5558_DIF_24BIT_MODE;
		break;
	case 32:
		bits = AK5558_DIF_32BIT_MODE;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, AK5558_02_CONTROL1, AK5558_BITS, bits);

	return 0;
}
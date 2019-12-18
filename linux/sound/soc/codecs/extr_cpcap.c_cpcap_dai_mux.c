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
typedef  scalar_t__ u16 ;
struct cpcap_audio {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPCAP_BIT_DIG_AUD_IN ; 
 int /*<<< orphan*/  CPCAP_BIT_DIG_AUD_IN_ST_DAC ; 
 int /*<<< orphan*/  CPCAP_REG_CDI ; 
 int /*<<< orphan*/  CPCAP_REG_SDACDI ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cpcap_dai_mux(struct cpcap_audio *cpcap, bool swap_dai_configuration)
{
	u16 hifi_val, voice_val;
	u16 hifi_mask = BIT(CPCAP_BIT_DIG_AUD_IN_ST_DAC);
	u16 voice_mask = BIT(CPCAP_BIT_DIG_AUD_IN);
	int err;



	if (!swap_dai_configuration) {
		/* Codec on DAI0, HiFi on DAI1 */
		voice_val = 0;
		hifi_val = hifi_mask;
	} else {
		/* Codec on DAI1, HiFi on DAI0 */
		voice_val = voice_mask;
		hifi_val = 0;
	}

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_CDI,
				 voice_mask, voice_val);
	if (err)
		return err;

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_SDACDI,
				 hifi_mask, hifi_val);
	if (err)
		return err;

	return 0;
}
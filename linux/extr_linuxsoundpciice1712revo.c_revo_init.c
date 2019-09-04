#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int subvendor; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2s_mclk_changed; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int akm_codecs; TYPE_2__ eeprom; struct snd_akm4xxx* akm; TYPE_1__ gpio; } ;
struct snd_akm4xxx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VT1724_REVO_MUTE ; 
#define  VT1724_SUBDEVICE_AUDIOPHILE192 130 
#define  VT1724_SUBDEVICE_REVOLUTION51 129 
#define  VT1724_SUBDEVICE_REVOLUTION71 128 
 int /*<<< orphan*/  akm_ap192 ; 
 int /*<<< orphan*/  akm_ap192_priv ; 
 int /*<<< orphan*/  akm_revo51 ; 
 int /*<<< orphan*/  akm_revo51_adc ; 
 int /*<<< orphan*/  akm_revo51_adc_priv ; 
 int /*<<< orphan*/  akm_revo51_priv ; 
 int /*<<< orphan*/  akm_revo_front ; 
 int /*<<< orphan*/  akm_revo_front_priv ; 
 int /*<<< orphan*/  akm_revo_surround ; 
 int /*<<< orphan*/  akm_revo_surround_priv ; 
 int ap192_ak4114_init (struct snd_ice1712*) ; 
 struct snd_akm4xxx* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptc_revo51_volume ; 
 int revo51_i2c_init (struct snd_ice1712*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  revo_i2s_mclk_changed ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_ice1712_akm4xxx_init (struct snd_akm4xxx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write_bits (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int revo_init(struct snd_ice1712 *ice)
{
	struct snd_akm4xxx *ak;
	int err;

	/* determine I2C, DACs and ADCs */
	switch (ice->eeprom.subvendor) {
	case VT1724_SUBDEVICE_REVOLUTION71:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
		ice->gpio.i2s_mclk_changed = revo_i2s_mclk_changed;
		break;
	case VT1724_SUBDEVICE_REVOLUTION51:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
		break;
	case VT1724_SUBDEVICE_AUDIOPHILE192:
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 2;
		break;
	default:
		snd_BUG();
		return -EINVAL;
	}

	/* second stage of initialization, analog parts and others */
	ak = ice->akm = kcalloc(2, sizeof(struct snd_akm4xxx), GFP_KERNEL);
	if (! ak)
		return -ENOMEM;
	switch (ice->eeprom.subvendor) {
	case VT1724_SUBDEVICE_REVOLUTION71:
		ice->akm_codecs = 2;
		err = snd_ice1712_akm4xxx_init(ak, &akm_revo_front,
						&akm_revo_front_priv, ice);
		if (err < 0)
			return err;
		err = snd_ice1712_akm4xxx_init(ak+1, &akm_revo_surround,
						&akm_revo_surround_priv, ice);
		if (err < 0)
			return err;
		/* unmute all codecs */
		snd_ice1712_gpio_write_bits(ice, VT1724_REVO_MUTE,
						VT1724_REVO_MUTE);
		break;
	case VT1724_SUBDEVICE_REVOLUTION51:
		ice->akm_codecs = 2;
		err = snd_ice1712_akm4xxx_init(ak, &akm_revo51,
					       &akm_revo51_priv, ice);
		if (err < 0)
			return err;
		err = snd_ice1712_akm4xxx_init(ak+1, &akm_revo51_adc,
					       &akm_revo51_adc_priv, ice);
		if (err < 0)
			return err;
		err = revo51_i2c_init(ice, &ptc_revo51_volume);
		if (err < 0)
			return err;
		/* unmute all codecs */
		snd_ice1712_gpio_write_bits(ice, VT1724_REVO_MUTE,
					    VT1724_REVO_MUTE);
		break;
	case VT1724_SUBDEVICE_AUDIOPHILE192:
		ice->akm_codecs = 1;
		err = snd_ice1712_akm4xxx_init(ak, &akm_ap192, &akm_ap192_priv,
					       ice);
		if (err < 0)
			return err;
		err = ap192_ak4114_init(ice);
		if (err < 0)
			return err;
		
		/* unmute all codecs */
		snd_ice1712_gpio_write_bits(ice, VT1724_REVO_MUTE,
					    VT1724_REVO_MUTE);
		break;
	}

	return 0;
}
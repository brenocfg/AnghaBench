#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int subvendor; int gpiodir; } ;
struct TYPE_8__ {int /*<<< orphan*/  stream_put; int /*<<< orphan*/  stream_get; int /*<<< orphan*/  default_put; int /*<<< orphan*/  default_get; int /*<<< orphan*/  setup_rate; int /*<<< orphan*/  open; } ;
struct TYPE_9__ {int /*<<< orphan*/  cs8403_bits; TYPE_2__ ops; } ;
struct TYPE_7__ {void* set_pro_rate; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int pm_suspend_enabled; int akm_codecs; TYPE_4__ eeprom; struct snd_akm4xxx* akm; TYPE_3__ spdif; TYPE_1__ gpio; TYPE_6__* i2c; TYPE_5__* card; int /*<<< orphan*/  pm_suspend; int /*<<< orphan*/  pm_resume; int /*<<< orphan*/  omni; } ;
struct snd_akm4xxx {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; struct snd_ice1712* private_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS8427_BASE_ADDR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned char ICE1712_DELTA_AP_CCLK ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
#define  ICE1712_SUBDEVICE_AUDIOPHILE 139 
#define  ICE1712_SUBDEVICE_DELTA1010 138 
#define  ICE1712_SUBDEVICE_DELTA1010E 137 
#define  ICE1712_SUBDEVICE_DELTA1010LT 136 
#define  ICE1712_SUBDEVICE_DELTA410 135 
#define  ICE1712_SUBDEVICE_DELTA44 134 
#define  ICE1712_SUBDEVICE_DELTA66 133 
#define  ICE1712_SUBDEVICE_DELTA66E 132 
#define  ICE1712_SUBDEVICE_DELTADIO2496 131 
#define  ICE1712_SUBDEVICE_EDIROLDA2496 130 
#define  ICE1712_SUBDEVICE_MEDIASTATION 129 
#define  ICE1712_SUBDEVICE_VX442 128 
 int /*<<< orphan*/  akm_audiophile ; 
 int /*<<< orphan*/  akm_audiophile_priv ; 
 int /*<<< orphan*/  akm_delta1010lt ; 
 int /*<<< orphan*/  akm_delta1010lt_priv ; 
 int /*<<< orphan*/  akm_delta410 ; 
 int /*<<< orphan*/  akm_delta410_priv ; 
 int /*<<< orphan*/  akm_delta44 ; 
 int /*<<< orphan*/  akm_delta44_priv ; 
 int /*<<< orphan*/  akm_delta66e ; 
 int /*<<< orphan*/  akm_delta66e_priv ; 
 int /*<<< orphan*/  akm_vx442 ; 
 int /*<<< orphan*/  akm_vx442_priv ; 
 int /*<<< orphan*/  ap_cs8427_i2c_ops ; 
 void* delta_1010_set_rate_val ; 
 int /*<<< orphan*/  delta_open_spdif ; 
 int /*<<< orphan*/  delta_setup_spdif ; 
 int /*<<< orphan*/  delta_spdif_default_get ; 
 int /*<<< orphan*/  delta_spdif_default_put ; 
 int /*<<< orphan*/  delta_spdif_stream_get ; 
 int /*<<< orphan*/  delta_spdif_stream_put ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_akm4xxx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_i2c_bus_create (TYPE_5__*,char*,int /*<<< orphan*/ *,TYPE_6__**) ; 
 int snd_ice1712_akm4xxx_init (struct snd_akm4xxx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_delta_cs8403_spdif_write (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_delta_resume ; 
 int /*<<< orphan*/  snd_ice1712_delta_suspend ; 
 int snd_ice1712_init_cs8427 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_ice1712_delta_init(struct snd_ice1712 *ice)
{
	int err;
	struct snd_akm4xxx *ak;
	unsigned char tmp;

	if (ice->eeprom.subvendor == ICE1712_SUBDEVICE_DELTA1010 &&
	    ice->eeprom.gpiodir == 0x7b)
		ice->eeprom.subvendor = ICE1712_SUBDEVICE_DELTA1010E;

	if (ice->eeprom.subvendor == ICE1712_SUBDEVICE_DELTA66 &&
	    ice->eeprom.gpiodir == 0xfb)
	    	ice->eeprom.subvendor = ICE1712_SUBDEVICE_DELTA66E;

	/* determine I2C, DACs and ADCs */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_AUDIOPHILE:
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 2;
		break;
	case ICE1712_SUBDEVICE_DELTA410:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 2;
		break;
	case ICE1712_SUBDEVICE_DELTA44:
	case ICE1712_SUBDEVICE_DELTA66:
		ice->num_total_dacs = ice->omni ? 8 : 4;
		ice->num_total_adcs = ice->omni ? 8 : 4;
		break;
	case ICE1712_SUBDEVICE_DELTA1010:
	case ICE1712_SUBDEVICE_DELTA1010E:
	case ICE1712_SUBDEVICE_DELTA1010LT:
	case ICE1712_SUBDEVICE_MEDIASTATION:
	case ICE1712_SUBDEVICE_EDIROLDA2496:
		ice->num_total_dacs = 8;
		ice->num_total_adcs = 8;
		break;
	case ICE1712_SUBDEVICE_DELTADIO2496:
		ice->num_total_dacs = 4;	/* two AK4324 codecs */
		break;
	case ICE1712_SUBDEVICE_VX442:
	case ICE1712_SUBDEVICE_DELTA66E:	/* omni not supported yet */
		ice->num_total_dacs = 4;
		ice->num_total_adcs = 4;
		break;
	}
#ifdef CONFIG_PM_SLEEP
	ice->pm_resume = snd_ice1712_delta_resume;
	ice->pm_suspend = snd_ice1712_delta_suspend;
	ice->pm_suspend_enabled = 1;
#endif
	/* initialize the SPI clock to high */
	tmp = snd_ice1712_read(ice, ICE1712_IREG_GPIO_DATA);
	tmp |= ICE1712_DELTA_AP_CCLK;
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp);
	udelay(5);

	/* initialize spdif */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_AUDIOPHILE:
	case ICE1712_SUBDEVICE_DELTA410:
	case ICE1712_SUBDEVICE_DELTA1010E:
	case ICE1712_SUBDEVICE_DELTA1010LT:
	case ICE1712_SUBDEVICE_VX442:
	case ICE1712_SUBDEVICE_DELTA66E:
		if ((err = snd_i2c_bus_create(ice->card, "ICE1712 GPIO 1", NULL, &ice->i2c)) < 0) {
			dev_err(ice->card->dev, "unable to create I2C bus\n");
			return err;
		}
		ice->i2c->private_data = ice;
		ice->i2c->ops = &ap_cs8427_i2c_ops;
		if ((err = snd_ice1712_init_cs8427(ice, CS8427_BASE_ADDR)) < 0)
			return err;
		break;
	case ICE1712_SUBDEVICE_DELTA1010:
	case ICE1712_SUBDEVICE_MEDIASTATION:
		ice->gpio.set_pro_rate = delta_1010_set_rate_val;
		break;
	case ICE1712_SUBDEVICE_DELTADIO2496:
		ice->gpio.set_pro_rate = delta_1010_set_rate_val;
		/* fall thru */
	case ICE1712_SUBDEVICE_DELTA66:
		ice->spdif.ops.open = delta_open_spdif;
		ice->spdif.ops.setup_rate = delta_setup_spdif;
		ice->spdif.ops.default_get = delta_spdif_default_get;
		ice->spdif.ops.default_put = delta_spdif_default_put;
		ice->spdif.ops.stream_get = delta_spdif_stream_get;
		ice->spdif.ops.stream_put = delta_spdif_stream_put;
		/* Set spdif defaults */
		snd_ice1712_delta_cs8403_spdif_write(ice, ice->spdif.cs8403_bits);
		break;
	}

	/* no analog? */
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_DELTA1010:
	case ICE1712_SUBDEVICE_DELTA1010E:
	case ICE1712_SUBDEVICE_DELTADIO2496:
	case ICE1712_SUBDEVICE_MEDIASTATION:
		return 0;
	}

	/* second stage of initialization, analog parts and others */
	ak = ice->akm = kmalloc(sizeof(struct snd_akm4xxx), GFP_KERNEL);
	if (! ak)
		return -ENOMEM;
	ice->akm_codecs = 1;

	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_AUDIOPHILE:
		err = snd_ice1712_akm4xxx_init(ak, &akm_audiophile, &akm_audiophile_priv, ice);
		break;
	case ICE1712_SUBDEVICE_DELTA410:
		err = snd_ice1712_akm4xxx_init(ak, &akm_delta410, &akm_delta410_priv, ice);
		break;
	case ICE1712_SUBDEVICE_DELTA1010LT:
	case ICE1712_SUBDEVICE_EDIROLDA2496:
		err = snd_ice1712_akm4xxx_init(ak, &akm_delta1010lt, &akm_delta1010lt_priv, ice);
		break;
	case ICE1712_SUBDEVICE_DELTA66:
	case ICE1712_SUBDEVICE_DELTA44:
		err = snd_ice1712_akm4xxx_init(ak, &akm_delta44, &akm_delta44_priv, ice);
		break;
	case ICE1712_SUBDEVICE_VX442:
		err = snd_ice1712_akm4xxx_init(ak, &akm_vx442, &akm_vx442_priv, ice);
		break;
	case ICE1712_SUBDEVICE_DELTA66E:
		err = snd_ice1712_akm4xxx_init(ak, &akm_delta66e, &akm_delta66e_priv, ice);
		break;
	default:
		snd_BUG();
		return -EINVAL;
	}

	return err;
}
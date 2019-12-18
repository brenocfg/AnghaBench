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
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int akm_codecs; struct snd_akm4xxx* akm; struct phase28_spec* spec; } ;
struct snd_akm4xxx {int dummy; } ;
struct phase28_spec {void** master; void** vol; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PHASE28_HP_SEL ; 
 unsigned int PHASE28_WM_CS ; 
 unsigned int PHASE28_WM_RESET ; 
 void* WM_VOL_MUTE ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_dir (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,unsigned short const,unsigned short const) ; 
 int /*<<< orphan*/  wm_set_vol (struct snd_ice1712*,int,void*,void*) ; 

__attribute__((used)) static int phase28_init(struct snd_ice1712 *ice)
{
	static const unsigned short wm_inits_phase28[] = {
		/* These come first to reduce init pop noise */
		0x1b, 0x044,	/* ADC Mux (AC'97 source) */
		0x1c, 0x00B,	/* Out Mux1 (VOUT1 = DAC+AUX, VOUT2 = DAC) */
		0x1d, 0x009,	/* Out Mux2 (VOUT2 = DAC, VOUT3 = DAC) */

		0x18, 0x000,	/* All power-up */

		0x16, 0x122,	/* I2S, normal polarity, 24bit */
		0x17, 0x022,	/* 256fs, slave mode */
		0x00, 0,	/* DAC1 analog mute */
		0x01, 0,	/* DAC2 analog mute */
		0x02, 0,	/* DAC3 analog mute */
		0x03, 0,	/* DAC4 analog mute */
		0x04, 0,	/* DAC5 analog mute */
		0x05, 0,	/* DAC6 analog mute */
		0x06, 0,	/* DAC7 analog mute */
		0x07, 0,	/* DAC8 analog mute */
		0x08, 0x100,	/* master analog mute */
		0x09, 0xff,	/* DAC1 digital full */
		0x0a, 0xff,	/* DAC2 digital full */
		0x0b, 0xff,	/* DAC3 digital full */
		0x0c, 0xff,	/* DAC4 digital full */
		0x0d, 0xff,	/* DAC5 digital full */
		0x0e, 0xff,	/* DAC6 digital full */
		0x0f, 0xff,	/* DAC7 digital full */
		0x10, 0xff,	/* DAC8 digital full */
		0x11, 0x1ff,	/* master digital full */
		0x12, 0x000,	/* phase normal */
		0x13, 0x090,	/* unmute DAC L/R */
		0x14, 0x000,	/* all unmute */
		0x15, 0x000,	/* no deemphasis, no ZFLG */
		0x19, 0x000,	/* -12dB ADC/L */
		0x1a, 0x000,	/* -12dB ADC/R */
		(unsigned short)-1
	};

	unsigned int tmp;
	struct snd_akm4xxx *ak;
	struct phase28_spec *spec;
	const unsigned short *p;
	int i;

	ice->num_total_dacs = 8;
	ice->num_total_adcs = 2;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;

	/* Initialize analog chips */
	ice->akm = kzalloc(sizeof(struct snd_akm4xxx), GFP_KERNEL);
	ak = ice->akm;
	if (!ak)
		return -ENOMEM;
	ice->akm_codecs = 1;

	snd_ice1712_gpio_set_dir(ice, 0x5fffff); /* fix this for time being */

	/* reset the wm codec as the SPI mode */
	snd_ice1712_save_gpio_status(ice);
	snd_ice1712_gpio_set_mask(ice, ~(PHASE28_WM_RESET|PHASE28_WM_CS|
					PHASE28_HP_SEL));

	tmp = snd_ice1712_gpio_read(ice);
	tmp &= ~PHASE28_WM_RESET;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);
	tmp |= PHASE28_WM_CS;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);
	tmp |= PHASE28_WM_RESET;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);

	p = wm_inits_phase28;
	for (; *p != (unsigned short)-1; p += 2)
		wm_put(ice, p[0], p[1]);

	snd_ice1712_restore_gpio_status(ice);

	spec->master[0] = WM_VOL_MUTE;
	spec->master[1] = WM_VOL_MUTE;
	for (i = 0; i < ice->num_total_dacs; i++) {
		spec->vol[i] = WM_VOL_MUTE;
		wm_set_vol(ice, i, spec->vol[i], spec->master[i % 2]);
	}

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ subvendor; } ;
struct snd_ice1712 {TYPE_1__ eeprom; struct aureon_spec* spec; } ;
struct aureon_spec {int cs8415_mux; } ;

/* Variables and functions */
 unsigned int AUREON_CS8415_CS ; 
 unsigned int AUREON_HP_SEL ; 
 unsigned int AUREON_WM_CS ; 
 unsigned int AUREON_WM_RESET ; 
 int /*<<< orphan*/  PCA9554_DIR ; 
 int /*<<< orphan*/  PCA9554_OUT ; 
 scalar_t__ VT1724_SUBDEVICE_PRODIGY71 ; 
 scalar_t__ VT1724_SUBDEVICE_PRODIGY71LT ; 
 scalar_t__ VT1724_SUBDEVICE_PRODIGY71XT ; 
 int aureon_ac97_init (struct snd_ice1712*) ; 
 int /*<<< orphan*/  aureon_pca9554_write (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aureon_set_headphone_amp (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  aureon_spi_write (struct snd_ice1712*,unsigned int,unsigned short const,int) ; 
 unsigned int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_dir (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,unsigned short const,unsigned short const) ; 

__attribute__((used)) static int aureon_reset(struct snd_ice1712 *ice)
{
	static const unsigned short wm_inits_aureon[] = {
		/* These come first to reduce init pop noise */
		0x1b, 0x044,		/* ADC Mux (AC'97 source) */
		0x1c, 0x00B,		/* Out Mux1 (VOUT1 = DAC+AUX, VOUT2 = DAC) */
		0x1d, 0x009,		/* Out Mux2 (VOUT2 = DAC, VOUT3 = DAC) */

		0x18, 0x000,		/* All power-up */

		0x16, 0x122,		/* I2S, normal polarity, 24bit */
		0x17, 0x022,		/* 256fs, slave mode */
		0x00, 0,		/* DAC1 analog mute */
		0x01, 0,		/* DAC2 analog mute */
		0x02, 0,		/* DAC3 analog mute */
		0x03, 0,		/* DAC4 analog mute */
		0x04, 0,		/* DAC5 analog mute */
		0x05, 0,		/* DAC6 analog mute */
		0x06, 0,		/* DAC7 analog mute */
		0x07, 0,		/* DAC8 analog mute */
		0x08, 0x100,		/* master analog mute */
		0x09, 0xff,		/* DAC1 digital full */
		0x0a, 0xff,		/* DAC2 digital full */
		0x0b, 0xff,		/* DAC3 digital full */
		0x0c, 0xff,		/* DAC4 digital full */
		0x0d, 0xff,		/* DAC5 digital full */
		0x0e, 0xff,		/* DAC6 digital full */
		0x0f, 0xff,		/* DAC7 digital full */
		0x10, 0xff,		/* DAC8 digital full */
		0x11, 0x1ff,		/* master digital full */
		0x12, 0x000,		/* phase normal */
		0x13, 0x090,		/* unmute DAC L/R */
		0x14, 0x000,		/* all unmute */
		0x15, 0x000,		/* no deemphasis, no ZFLG */
		0x19, 0x000,		/* -12dB ADC/L */
		0x1a, 0x000,		/* -12dB ADC/R */
		(unsigned short)-1
	};
	static const unsigned short wm_inits_prodigy[] = {

		/* These come first to reduce init pop noise */
		0x1b, 0x000,		/* ADC Mux */
		0x1c, 0x009,		/* Out Mux1 */
		0x1d, 0x009,		/* Out Mux2 */

		0x18, 0x000,		/* All power-up */

		0x16, 0x022,		/* I2S, normal polarity, 24bit, high-pass on */
		0x17, 0x006,		/* 128fs, slave mode */

		0x00, 0,		/* DAC1 analog mute */
		0x01, 0,		/* DAC2 analog mute */
		0x02, 0,		/* DAC3 analog mute */
		0x03, 0,		/* DAC4 analog mute */
		0x04, 0,		/* DAC5 analog mute */
		0x05, 0,		/* DAC6 analog mute */
		0x06, 0,		/* DAC7 analog mute */
		0x07, 0,		/* DAC8 analog mute */
		0x08, 0x100,		/* master analog mute */

		0x09, 0x7f,		/* DAC1 digital full */
		0x0a, 0x7f,		/* DAC2 digital full */
		0x0b, 0x7f,		/* DAC3 digital full */
		0x0c, 0x7f,		/* DAC4 digital full */
		0x0d, 0x7f,		/* DAC5 digital full */
		0x0e, 0x7f,		/* DAC6 digital full */
		0x0f, 0x7f,		/* DAC7 digital full */
		0x10, 0x7f,		/* DAC8 digital full */
		0x11, 0x1FF,		/* master digital full */

		0x12, 0x000,		/* phase normal */
		0x13, 0x090,		/* unmute DAC L/R */
		0x14, 0x000,		/* all unmute */
		0x15, 0x000,		/* no deemphasis, no ZFLG */

		0x19, 0x000,		/* -12dB ADC/L */
		0x1a, 0x000,		/* -12dB ADC/R */
		(unsigned short)-1

	};
	static const unsigned short cs_inits[] = {
		0x0441, /* RUN */
		0x0180, /* no mute, OMCK output on RMCK pin */
		0x0201, /* S/PDIF source on RXP1 */
		0x0605, /* slave, 24bit, MSB on second OSCLK, SDOUT for right channel when OLRCK is high */
		(unsigned short)-1
	};
	unsigned int tmp;
	const unsigned short *p;
	int err;
	struct aureon_spec *spec = ice->spec;

	err = aureon_ac97_init(ice);
	if (err != 0)
		return err;

	snd_ice1712_gpio_set_dir(ice, 0x5fffff); /* fix this for the time being */

	/* reset the wm codec as the SPI mode */
	snd_ice1712_save_gpio_status(ice);
	snd_ice1712_gpio_set_mask(ice, ~(AUREON_WM_RESET|AUREON_WM_CS|AUREON_CS8415_CS|AUREON_HP_SEL));

	tmp = snd_ice1712_gpio_read(ice);
	tmp &= ~AUREON_WM_RESET;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);
	tmp |= AUREON_WM_CS | AUREON_CS8415_CS;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);
	tmp |= AUREON_WM_RESET;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);

	/* initialize WM8770 codec */
	if (ice->eeprom.subvendor == VT1724_SUBDEVICE_PRODIGY71 ||
		ice->eeprom.subvendor == VT1724_SUBDEVICE_PRODIGY71LT ||
		ice->eeprom.subvendor == VT1724_SUBDEVICE_PRODIGY71XT)
		p = wm_inits_prodigy;
	else
		p = wm_inits_aureon;
	for (; *p != (unsigned short)-1; p += 2)
		wm_put(ice, p[0], p[1]);

	/* initialize CS8415A codec */
	if (ice->eeprom.subvendor != VT1724_SUBDEVICE_PRODIGY71LT &&
	    ice->eeprom.subvendor != VT1724_SUBDEVICE_PRODIGY71XT) {
		for (p = cs_inits; *p != (unsigned short)-1; p++)
			aureon_spi_write(ice, AUREON_CS8415_CS, *p | 0x200000, 24);
		spec->cs8415_mux = 1;

		aureon_set_headphone_amp(ice, 1);
	}

	snd_ice1712_restore_gpio_status(ice);

	/* initialize PCA9554 pin directions & set default input */
	aureon_pca9554_write(ice, PCA9554_DIR, 0x00);
	aureon_pca9554_write(ice, PCA9554_OUT, 0x00);   /* internal AUX */
	return 0;
}
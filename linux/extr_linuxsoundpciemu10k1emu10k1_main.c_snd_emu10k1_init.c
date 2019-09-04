#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {unsigned int addr; } ;
struct TYPE_6__ {unsigned int addr; } ;
struct snd_emu10k1 {unsigned int* spdif_bits; int** i2c_capture_volume; unsigned int address_mode; int revision; int model; scalar_t__ port; scalar_t__ audigy; TYPE_4__* card_capabilities; TYPE_3__ silent_page; TYPE_2__ ptb_pages; TYPE_1__* card; } ;
struct TYPE_8__ {scalar_t__ i2c_adc; scalar_t__ emu_model; scalar_t__ spi_dac; scalar_t__ ca0108_chip; scalar_t__ ca0151_chip; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97SLOT ; 
 unsigned int AC97SLOT_REAR_LEFT ; 
 unsigned int AC97SLOT_REAR_RIGHT ; 
 int /*<<< orphan*/  ADCBA ; 
 int /*<<< orphan*/  ADCBS ; 
 unsigned int ADCBS_BUFSIZE_NONE ; 
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 scalar_t__ A_IOCFG ; 
 unsigned int A_IOCFG_GPOUT0 ; 
 unsigned int A_IOCFG_GPOUT1 ; 
 unsigned int A_IOCFG_GPOUT2 ; 
 int /*<<< orphan*/  A_SPDIF_SAMPLERATE ; 
 int CAPTURE_P16V_SOURCE ; 
 int /*<<< orphan*/  CLIEH ; 
 int /*<<< orphan*/  CLIEL ; 
 int /*<<< orphan*/  FXBA ; 
 int /*<<< orphan*/  FXBS ; 
 scalar_t__ HCFG ; 
 scalar_t__ HCFG2 ; 
 unsigned int HCFG_AC3ENABLE_CDSPDIF ; 
 unsigned int HCFG_AC3ENABLE_GPSPDIF ; 
 unsigned int HCFG_AUDIOENABLE ; 
 unsigned int HCFG_AUTOMUTE ; 
 unsigned int HCFG_AUTOMUTE_ASYNC ; 
 unsigned int HCFG_EMU32_SLAVE ; 
 unsigned int HCFG_EXPANDED_MEM ; 
 unsigned int HCFG_GPOUT1 ; 
 unsigned int HCFG_GPOUT2 ; 
 unsigned int HCFG_JOYENABLE ; 
 unsigned int HCFG_LOCKSOUNDCACHE ; 
 unsigned int HCFG_LOCKTANKCACHE_MASK ; 
 unsigned int HCFG_MUTEBUTTONENABLE ; 
 scalar_t__ INTE ; 
 int /*<<< orphan*/  MAPA ; 
 int /*<<< orphan*/  MAPB ; 
 unsigned int MAP_PTI_MASK0 ; 
 unsigned int MAP_PTI_MASK1 ; 
 int /*<<< orphan*/  MICBA ; 
 int /*<<< orphan*/  MICBS ; 
 int NUM_G ; 
 int P17V_I2S_SRC_SEL ; 
 int /*<<< orphan*/  PTB ; 
 int /*<<< orphan*/  SOLEH ; 
 int /*<<< orphan*/  SOLEL ; 
 int /*<<< orphan*/  SPBYPASS ; 
 unsigned int SPBYPASS_FORMAT ; 
 int /*<<< orphan*/  SPCS0 ; 
 int /*<<< orphan*/  SPCS1 ; 
 int /*<<< orphan*/  SPCS2 ; 
 int SRCMULTI_ENABLE ; 
 int SRCSel ; 
 int /*<<< orphan*/  TCB ; 
 int /*<<< orphan*/  TCBS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ ** i2c_adc_init ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  snd_emu10k1_i2c_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr20_write (struct snd_emu10k1*,int,int /*<<< orphan*/ ,int) ; 
 int snd_emu10k1_ptr_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  snd_emu10k1_spi_write (struct snd_emu10k1*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emu10k1_voice_init (struct snd_emu10k1*,int) ; 
 int /*<<< orphan*/ ** spi_dac_init ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_emu10k1_init(struct snd_emu10k1 *emu, int enable_ir, int resume)
{
	unsigned int silent_page;
	int ch;
	u32 tmp;

	/* disable audio and lock cache */
	outl(HCFG_LOCKSOUNDCACHE | HCFG_LOCKTANKCACHE_MASK |
		HCFG_MUTEBUTTONENABLE, emu->port + HCFG);

	/* reset recording buffers */
	snd_emu10k1_ptr_write(emu, MICBS, 0, ADCBS_BUFSIZE_NONE);
	snd_emu10k1_ptr_write(emu, MICBA, 0, 0);
	snd_emu10k1_ptr_write(emu, FXBS, 0, ADCBS_BUFSIZE_NONE);
	snd_emu10k1_ptr_write(emu, FXBA, 0, 0);
	snd_emu10k1_ptr_write(emu, ADCBS, 0, ADCBS_BUFSIZE_NONE);
	snd_emu10k1_ptr_write(emu, ADCBA, 0, 0);

	/* disable channel interrupt */
	outl(0, emu->port + INTE);
	snd_emu10k1_ptr_write(emu, CLIEL, 0, 0);
	snd_emu10k1_ptr_write(emu, CLIEH, 0, 0);
	snd_emu10k1_ptr_write(emu, SOLEL, 0, 0);
	snd_emu10k1_ptr_write(emu, SOLEH, 0, 0);

	if (emu->audigy) {
		/* set SPDIF bypass mode */
		snd_emu10k1_ptr_write(emu, SPBYPASS, 0, SPBYPASS_FORMAT);
		/* enable rear left + rear right AC97 slots */
		snd_emu10k1_ptr_write(emu, AC97SLOT, 0, AC97SLOT_REAR_RIGHT |
				      AC97SLOT_REAR_LEFT);
	}

	/* init envelope engine */
	for (ch = 0; ch < NUM_G; ch++)
		snd_emu10k1_voice_init(emu, ch);

	snd_emu10k1_ptr_write(emu, SPCS0, 0, emu->spdif_bits[0]);
	snd_emu10k1_ptr_write(emu, SPCS1, 0, emu->spdif_bits[1]);
	snd_emu10k1_ptr_write(emu, SPCS2, 0, emu->spdif_bits[2]);

	if (emu->card_capabilities->ca0151_chip) { /* audigy2 */
		/* Hacks for Alice3 to work independent of haP16V driver */
		/* Setup SRCMulti_I2S SamplingRate */
		tmp = snd_emu10k1_ptr_read(emu, A_SPDIF_SAMPLERATE, 0);
		tmp &= 0xfffff1ff;
		tmp |= (0x2<<9);
		snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, 0, tmp);

		/* Setup SRCSel (Enable Spdif,I2S SRCMulti) */
		snd_emu10k1_ptr20_write(emu, SRCSel, 0, 0x14);
		/* Setup SRCMulti Input Audio Enable */
		/* Use 0xFFFFFFFF to enable P16V sounds. */
		snd_emu10k1_ptr20_write(emu, SRCMULTI_ENABLE, 0, 0xFFFFFFFF);

		/* Enabled Phased (8-channel) P16V playback */
		outl(0x0201, emu->port + HCFG2);
		/* Set playback routing. */
		snd_emu10k1_ptr20_write(emu, CAPTURE_P16V_SOURCE, 0, 0x78e4);
	}
	if (emu->card_capabilities->ca0108_chip) { /* audigy2 Value */
		/* Hacks for Alice3 to work independent of haP16V driver */
		dev_info(emu->card->dev, "Audigy2 value: Special config.\n");
		/* Setup SRCMulti_I2S SamplingRate */
		tmp = snd_emu10k1_ptr_read(emu, A_SPDIF_SAMPLERATE, 0);
		tmp &= 0xfffff1ff;
		tmp |= (0x2<<9);
		snd_emu10k1_ptr_write(emu, A_SPDIF_SAMPLERATE, 0, tmp);

		/* Setup SRCSel (Enable Spdif,I2S SRCMulti) */
		outl(0x600000, emu->port + 0x20);
		outl(0x14, emu->port + 0x24);

		/* Setup SRCMulti Input Audio Enable */
		outl(0x7b0000, emu->port + 0x20);
		outl(0xFF000000, emu->port + 0x24);

		/* Setup SPDIF Out Audio Enable */
		/* The Audigy 2 Value has a separate SPDIF out,
		 * so no need for a mixer switch
		 */
		outl(0x7a0000, emu->port + 0x20);
		outl(0xFF000000, emu->port + 0x24);
		tmp = inl(emu->port + A_IOCFG) & ~0x8; /* Clear bit 3 */
		outl(tmp, emu->port + A_IOCFG);
	}
	if (emu->card_capabilities->spi_dac) { /* Audigy 2 ZS Notebook with DAC Wolfson WM8768/WM8568 */
		int size, n;

		size = ARRAY_SIZE(spi_dac_init);
		for (n = 0; n < size; n++)
			snd_emu10k1_spi_write(emu, spi_dac_init[n]);

		snd_emu10k1_ptr20_write(emu, 0x60, 0, 0x10);
		/* Enable GPIOs
		 * GPIO0: Unknown
		 * GPIO1: Speakers-enabled.
		 * GPIO2: Unknown
		 * GPIO3: Unknown
		 * GPIO4: IEC958 Output on.
		 * GPIO5: Unknown
		 * GPIO6: Unknown
		 * GPIO7: Unknown
		 */
		outl(0x76, emu->port + A_IOCFG); /* Windows uses 0x3f76 */
	}
	if (emu->card_capabilities->i2c_adc) { /* Audigy 2 ZS Notebook with ADC Wolfson WM8775 */
		int size, n;

		snd_emu10k1_ptr20_write(emu, P17V_I2S_SRC_SEL, 0, 0x2020205f);
		tmp = inl(emu->port + A_IOCFG);
		outl(tmp | 0x4, emu->port + A_IOCFG);  /* Set bit 2 for mic input */
		tmp = inl(emu->port + A_IOCFG);
		size = ARRAY_SIZE(i2c_adc_init);
		for (n = 0; n < size; n++)
			snd_emu10k1_i2c_write(emu, i2c_adc_init[n][0], i2c_adc_init[n][1]);
		for (n = 0; n < 4; n++) {
			emu->i2c_capture_volume[n][0] = 0xcf;
			emu->i2c_capture_volume[n][1] = 0xcf;
		}
	}


	snd_emu10k1_ptr_write(emu, PTB, 0, emu->ptb_pages.addr);
	snd_emu10k1_ptr_write(emu, TCB, 0, 0);	/* taken from original driver */
	snd_emu10k1_ptr_write(emu, TCBS, 0, 4);	/* taken from original driver */

	silent_page = (emu->silent_page.addr << emu->address_mode) | (emu->address_mode ? MAP_PTI_MASK1 : MAP_PTI_MASK0);
	for (ch = 0; ch < NUM_G; ch++) {
		snd_emu10k1_ptr_write(emu, MAPA, ch, silent_page);
		snd_emu10k1_ptr_write(emu, MAPB, ch, silent_page);
	}

	if (emu->card_capabilities->emu_model) {
		outl(HCFG_AUTOMUTE_ASYNC |
			HCFG_EMU32_SLAVE |
			HCFG_AUDIOENABLE, emu->port + HCFG);
	/*
	 *  Hokay, setup HCFG
	 *   Mute Disable Audio = 0
	 *   Lock Tank Memory = 1
	 *   Lock Sound Memory = 0
	 *   Auto Mute = 1
	 */
	} else if (emu->audigy) {
		if (emu->revision == 4) /* audigy2 */
			outl(HCFG_AUDIOENABLE |
			     HCFG_AC3ENABLE_CDSPDIF |
			     HCFG_AC3ENABLE_GPSPDIF |
			     HCFG_AUTOMUTE | HCFG_JOYENABLE, emu->port + HCFG);
		else
			outl(HCFG_AUTOMUTE | HCFG_JOYENABLE, emu->port + HCFG);
	/* FIXME: Remove all these emu->model and replace it with a card recognition parameter,
	 * e.g. card_capabilities->joystick */
	} else if (emu->model == 0x20 ||
	    emu->model == 0xc400 ||
	    (emu->model == 0x21 && emu->revision < 6))
		outl(HCFG_LOCKTANKCACHE_MASK | HCFG_AUTOMUTE, emu->port + HCFG);
	else
		/* With on-chip joystick */
		outl(HCFG_LOCKTANKCACHE_MASK | HCFG_AUTOMUTE | HCFG_JOYENABLE, emu->port + HCFG);

	if (enable_ir) {	/* enable IR for SB Live */
		if (emu->card_capabilities->emu_model) {
			;  /* Disable all access to A_IOCFG for the emu1010 */
		} else if (emu->card_capabilities->i2c_adc) {
			;  /* Disable A_IOCFG for Audigy 2 ZS Notebook */
		} else if (emu->audigy) {
			unsigned int reg = inl(emu->port + A_IOCFG);
			outl(reg | A_IOCFG_GPOUT2, emu->port + A_IOCFG);
			udelay(500);
			outl(reg | A_IOCFG_GPOUT1 | A_IOCFG_GPOUT2, emu->port + A_IOCFG);
			udelay(100);
			outl(reg, emu->port + A_IOCFG);
		} else {
			unsigned int reg = inl(emu->port + HCFG);
			outl(reg | HCFG_GPOUT2, emu->port + HCFG);
			udelay(500);
			outl(reg | HCFG_GPOUT1 | HCFG_GPOUT2, emu->port + HCFG);
			udelay(100);
			outl(reg, emu->port + HCFG);
		}
	}

	if (emu->card_capabilities->emu_model) {
		;  /* Disable all access to A_IOCFG for the emu1010 */
	} else if (emu->card_capabilities->i2c_adc) {
		;  /* Disable A_IOCFG for Audigy 2 ZS Notebook */
	} else if (emu->audigy) {	/* enable analog output */
		unsigned int reg = inl(emu->port + A_IOCFG);
		outl(reg | A_IOCFG_GPOUT0, emu->port + A_IOCFG);
	}

	if (emu->address_mode == 0) {
		/* use 16M in 4G */
		outl(inl(emu->port + HCFG) | HCFG_EXPANDED_MEM, emu->port + HCFG);
	}

	return 0;
}
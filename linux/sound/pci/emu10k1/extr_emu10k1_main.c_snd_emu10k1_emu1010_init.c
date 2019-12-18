#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int optical_in; int optical_out; int adc_pads; int dac_pads; int* output_source; int internal_clock; } ;
struct snd_emu10k1 {TYPE_3__ emu1010; TYPE_2__* card_capabilities; scalar_t__ port; TYPE_1__* card; int /*<<< orphan*/  firmware; } ;
struct TYPE_5__ {scalar_t__ emu_model; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int EMU_DST_ALICE2_EMU32_0 ; 
 unsigned int EMU_DST_ALICE2_EMU32_1 ; 
 unsigned int EMU_DST_ALICE2_EMU32_2 ; 
 unsigned int EMU_DST_ALICE2_EMU32_3 ; 
 unsigned int EMU_DST_ALICE2_EMU32_4 ; 
 unsigned int EMU_DST_ALICE2_EMU32_5 ; 
 unsigned int EMU_DST_ALICE2_EMU32_6 ; 
 unsigned int EMU_DST_ALICE2_EMU32_7 ; 
 unsigned int EMU_DST_ALICE2_EMU32_8 ; 
 unsigned int EMU_DST_ALICE2_EMU32_9 ; 
 unsigned int EMU_DST_ALICE2_EMU32_A ; 
 unsigned int EMU_DST_ALICE2_EMU32_B ; 
 unsigned int EMU_DST_ALICE2_EMU32_C ; 
 unsigned int EMU_DST_ALICE2_EMU32_D ; 
 unsigned int EMU_DST_ALICE2_EMU32_E ; 
 unsigned int EMU_DST_ALICE2_EMU32_F ; 
 unsigned int EMU_DST_ALICE_I2S0_LEFT ; 
 unsigned int EMU_DST_ALICE_I2S0_RIGHT ; 
 unsigned int EMU_DST_ALICE_I2S1_LEFT ; 
 unsigned int EMU_DST_ALICE_I2S1_RIGHT ; 
 unsigned int EMU_DST_ALICE_I2S2_LEFT ; 
 unsigned int EMU_DST_ALICE_I2S2_RIGHT ; 
 unsigned int EMU_DST_DOCK_DAC1_LEFT1 ; 
 unsigned int EMU_DST_DOCK_DAC1_RIGHT1 ; 
 unsigned int EMU_DST_DOCK_DAC2_LEFT1 ; 
 unsigned int EMU_DST_DOCK_DAC2_RIGHT1 ; 
 unsigned int EMU_DST_DOCK_DAC3_LEFT1 ; 
 unsigned int EMU_DST_DOCK_DAC3_RIGHT1 ; 
 unsigned int EMU_DST_DOCK_DAC4_LEFT1 ; 
 unsigned int EMU_DST_DOCK_DAC4_RIGHT1 ; 
 unsigned int EMU_DST_DOCK_PHONES_LEFT1 ; 
 unsigned int EMU_DST_DOCK_PHONES_RIGHT1 ; 
 unsigned int EMU_DST_DOCK_SPDIF_LEFT1 ; 
 unsigned int EMU_DST_DOCK_SPDIF_RIGHT1 ; 
 unsigned int EMU_DST_HAMOA_DAC_LEFT1 ; 
 unsigned int EMU_DST_HAMOA_DAC_RIGHT1 ; 
 unsigned int EMU_DST_HANA_ADAT ; 
 unsigned int EMU_DST_HANA_SPDIF_LEFT1 ; 
 unsigned int EMU_DST_HANA_SPDIF_RIGHT1 ; 
 unsigned int EMU_DST_MANA_DAC_LEFT ; 
 unsigned int EMU_DST_MANA_DAC_RIGHT ; 
 int /*<<< orphan*/  EMU_HANA_ADC_PADS ; 
 int /*<<< orphan*/  EMU_HANA_DAC_PADS ; 
 int /*<<< orphan*/  EMU_HANA_DEFCLOCK ; 
 int /*<<< orphan*/  EMU_HANA_DOCK_LEDS_2 ; 
 int /*<<< orphan*/  EMU_HANA_DOCK_MISC ; 
 int /*<<< orphan*/  EMU_HANA_DOCK_PWR ; 
 int EMU_HANA_DOCK_PWR_ON ; 
 int /*<<< orphan*/  EMU_HANA_FPGA_CONFIG ; 
 int /*<<< orphan*/  EMU_HANA_ID ; 
 int /*<<< orphan*/  EMU_HANA_IRQ_ENABLE ; 
 int /*<<< orphan*/  EMU_HANA_MAJOR_REV ; 
 int /*<<< orphan*/  EMU_HANA_MIDI_IN ; 
 int /*<<< orphan*/  EMU_HANA_MIDI_OUT ; 
 int /*<<< orphan*/  EMU_HANA_MINOR_REV ; 
 int EMU_HANA_OPTICAL_IN_ADAT ; 
 int EMU_HANA_OPTICAL_OUT_ADAT ; 
 int /*<<< orphan*/  EMU_HANA_OPTICAL_TYPE ; 
 int /*<<< orphan*/  EMU_HANA_OPTION_CARDS ; 
 int /*<<< orphan*/  EMU_HANA_SPDIF_MODE ; 
 int /*<<< orphan*/  EMU_HANA_UNMUTE ; 
 int /*<<< orphan*/  EMU_HANA_WCLOCK ; 
 int EMU_HANA_WCLOCK_INT_48K ; 
 scalar_t__ EMU_MODEL_EMU1616 ; 
 scalar_t__ EMU_SRC_ALICE_EMU32A ; 
 scalar_t__ EMU_SRC_ALICE_EMU32B ; 
 scalar_t__ EMU_SRC_DOCK_ADC1_LEFT1 ; 
 scalar_t__ EMU_SRC_DOCK_ADC1_RIGHT1 ; 
 scalar_t__ EMU_SRC_DOCK_ADC2_LEFT1 ; 
 scalar_t__ EMU_SRC_DOCK_ADC2_RIGHT1 ; 
 scalar_t__ EMU_SRC_DOCK_ADC3_LEFT1 ; 
 scalar_t__ EMU_SRC_DOCK_ADC3_RIGHT1 ; 
 scalar_t__ EMU_SRC_DOCK_MIC_A1 ; 
 scalar_t__ EMU_SRC_DOCK_MIC_B1 ; 
 scalar_t__ EMU_SRC_HAMOA_ADC_LEFT1 ; 
 scalar_t__ EMU_SRC_HAMOA_ADC_LEFT2 ; 
 scalar_t__ EMU_SRC_HAMOA_ADC_LEFT3 ; 
 scalar_t__ EMU_SRC_HAMOA_ADC_LEFT4 ; 
 scalar_t__ EMU_SRC_HAMOA_ADC_RIGHT1 ; 
 scalar_t__ EMU_SRC_HAMOA_ADC_RIGHT2 ; 
 scalar_t__ EMU_SRC_HAMOA_ADC_RIGHT3 ; 
 scalar_t__ EMU_SRC_HAMOA_ADC_RIGHT4 ; 
 scalar_t__ EMU_SRC_HANA_ADAT ; 
 scalar_t__ EMU_SRC_SILENCE ; 
 int ENODEV ; 
 scalar_t__ HCFG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_emu1010_fpga_link_dst_src_write (struct snd_emu10k1*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  snd_emu1010_fpga_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  snd_emu1010_fpga_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int) ; 
 int snd_emu1010_load_firmware (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_emu10k1_emu1010_init(struct snd_emu10k1 *emu)
{
	unsigned int i;
	u32 tmp, tmp2, reg;
	int err;

	dev_info(emu->card->dev, "emu1010: Special config.\n");
	/* AC97 2.1, Any 16Meg of 4Gig address, Auto-Mute, EMU32 Slave,
	 * Lock Sound Memory Cache, Lock Tank Memory Cache,
	 * Mute all codecs.
	 */
	outl(0x0005a00c, emu->port + HCFG);
	/* AC97 2.1, Any 16Meg of 4Gig address, Auto-Mute, EMU32 Slave,
	 * Lock Tank Memory Cache,
	 * Mute all codecs.
	 */
	outl(0x0005a004, emu->port + HCFG);
	/* AC97 2.1, Any 16Meg of 4Gig address, Auto-Mute, EMU32 Slave,
	 * Mute all codecs.
	 */
	outl(0x0005a000, emu->port + HCFG);
	/* AC97 2.1, Any 16Meg of 4Gig address, Auto-Mute, EMU32 Slave,
	 * Mute all codecs.
	 */
	outl(0x0005a000, emu->port + HCFG);

	/* Disable 48Volt power to Audio Dock */
	snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_PWR, 0);

	/* ID, should read & 0x7f = 0x55. (Bit 7 is the IRQ bit) */
	snd_emu1010_fpga_read(emu, EMU_HANA_ID, &reg);
	dev_dbg(emu->card->dev, "reg1 = 0x%x\n", reg);
	if ((reg & 0x3f) == 0x15) {
		/* FPGA netlist already present so clear it */
		/* Return to programming mode */

		snd_emu1010_fpga_write(emu, EMU_HANA_FPGA_CONFIG, 0x02);
	}
	snd_emu1010_fpga_read(emu, EMU_HANA_ID, &reg);
	dev_dbg(emu->card->dev, "reg2 = 0x%x\n", reg);
	if ((reg & 0x3f) == 0x15) {
		/* FPGA failed to return to programming mode */
		dev_info(emu->card->dev,
			 "emu1010: FPGA failed to return to programming mode\n");
		return -ENODEV;
	}
	dev_info(emu->card->dev, "emu1010: EMU_HANA_ID = 0x%x\n", reg);

	err = snd_emu1010_load_firmware(emu, 0, &emu->firmware);
	if (err < 0) {
		dev_info(emu->card->dev, "emu1010: Loading Firmware failed\n");
		return err;
	}

	/* ID, should read & 0x7f = 0x55 when FPGA programmed. */
	snd_emu1010_fpga_read(emu, EMU_HANA_ID, &reg);
	if ((reg & 0x3f) != 0x15) {
		/* FPGA failed to be programmed */
		dev_info(emu->card->dev,
			 "emu1010: Loading Hana Firmware file failed, reg = 0x%x\n",
			 reg);
		return -ENODEV;
	}

	dev_info(emu->card->dev, "emu1010: Hana Firmware loaded\n");
	snd_emu1010_fpga_read(emu, EMU_HANA_MAJOR_REV, &tmp);
	snd_emu1010_fpga_read(emu, EMU_HANA_MINOR_REV, &tmp2);
	dev_info(emu->card->dev, "emu1010: Hana version: %u.%u\n", tmp, tmp2);
	/* Enable 48Volt power to Audio Dock */
	snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_PWR, EMU_HANA_DOCK_PWR_ON);

	snd_emu1010_fpga_read(emu, EMU_HANA_OPTION_CARDS, &reg);
	dev_info(emu->card->dev, "emu1010: Card options = 0x%x\n", reg);
	snd_emu1010_fpga_read(emu, EMU_HANA_OPTION_CARDS, &reg);
	dev_info(emu->card->dev, "emu1010: Card options = 0x%x\n", reg);
	snd_emu1010_fpga_read(emu, EMU_HANA_OPTICAL_TYPE, &tmp);
	/* Optical -> ADAT I/O  */
	/* 0 : SPDIF
	 * 1 : ADAT
	 */
	emu->emu1010.optical_in = 1; /* IN_ADAT */
	emu->emu1010.optical_out = 1; /* IN_ADAT */
	tmp = 0;
	tmp = (emu->emu1010.optical_in ? EMU_HANA_OPTICAL_IN_ADAT : 0) |
		(emu->emu1010.optical_out ? EMU_HANA_OPTICAL_OUT_ADAT : 0);
	snd_emu1010_fpga_write(emu, EMU_HANA_OPTICAL_TYPE, tmp);
	snd_emu1010_fpga_read(emu, EMU_HANA_ADC_PADS, &tmp);
	/* Set no attenuation on Audio Dock pads. */
	snd_emu1010_fpga_write(emu, EMU_HANA_ADC_PADS, 0x00);
	emu->emu1010.adc_pads = 0x00;
	snd_emu1010_fpga_read(emu, EMU_HANA_DOCK_MISC, &tmp);
	/* Unmute Audio dock DACs, Headphone source DAC-4. */
	snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_MISC, 0x30);
	snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_LEDS_2, 0x12);
	snd_emu1010_fpga_read(emu, EMU_HANA_DAC_PADS, &tmp);
	/* DAC PADs. */
	snd_emu1010_fpga_write(emu, EMU_HANA_DAC_PADS, 0x0f);
	emu->emu1010.dac_pads = 0x0f;
	snd_emu1010_fpga_read(emu, EMU_HANA_DOCK_MISC, &tmp);
	snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_MISC, 0x30);
	snd_emu1010_fpga_read(emu, EMU_HANA_SPDIF_MODE, &tmp);
	/* SPDIF Format. Set Consumer mode, 24bit, copy enable */
	snd_emu1010_fpga_write(emu, EMU_HANA_SPDIF_MODE, 0x10);
	/* MIDI routing */
	snd_emu1010_fpga_write(emu, EMU_HANA_MIDI_IN, 0x19);
	/* Unknown. */
	snd_emu1010_fpga_write(emu, EMU_HANA_MIDI_OUT, 0x0c);
	/* IRQ Enable: All on */
	/* snd_emu1010_fpga_write(emu, 0x09, 0x0f ); */
	/* IRQ Enable: All off */
	snd_emu1010_fpga_write(emu, EMU_HANA_IRQ_ENABLE, 0x00);

	snd_emu1010_fpga_read(emu, EMU_HANA_OPTION_CARDS, &reg);
	dev_info(emu->card->dev, "emu1010: Card options3 = 0x%x\n", reg);
	/* Default WCLK set to 48kHz. */
	snd_emu1010_fpga_write(emu, EMU_HANA_DEFCLOCK, 0x00);
	/* Word Clock source, Internal 48kHz x1 */
	snd_emu1010_fpga_write(emu, EMU_HANA_WCLOCK, EMU_HANA_WCLOCK_INT_48K);
	/* snd_emu1010_fpga_write(emu, EMU_HANA_WCLOCK, EMU_HANA_WCLOCK_INT_48K | EMU_HANA_WCLOCK_4X); */
	/* Audio Dock LEDs. */
	snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_LEDS_2, 0x12);

#if 0
	/* For 96kHz */
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_0, EMU_SRC_HAMOA_ADC_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_1, EMU_SRC_HAMOA_ADC_RIGHT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_4, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_5, EMU_SRC_HAMOA_ADC_RIGHT2);
#endif
#if 0
	/* For 192kHz */
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_0, EMU_SRC_HAMOA_ADC_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_1, EMU_SRC_HAMOA_ADC_RIGHT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_2, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_3, EMU_SRC_HAMOA_ADC_RIGHT2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_4, EMU_SRC_HAMOA_ADC_LEFT3);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_5, EMU_SRC_HAMOA_ADC_RIGHT3);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_6, EMU_SRC_HAMOA_ADC_LEFT4);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_7, EMU_SRC_HAMOA_ADC_RIGHT4);
#endif
#if 1
	/* For 48kHz */
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_0, EMU_SRC_DOCK_MIC_A1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_1, EMU_SRC_DOCK_MIC_B1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_2, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_3, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_4, EMU_SRC_DOCK_ADC1_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_5, EMU_SRC_DOCK_ADC1_RIGHT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_6, EMU_SRC_DOCK_ADC2_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_7, EMU_SRC_DOCK_ADC2_RIGHT1);
	/* Pavel Hofman - setting defaults for 8 more capture channels
	 * Defaults only, users will set their own values anyways, let's
	 * just copy/paste.
	 */

	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_8, EMU_SRC_DOCK_MIC_A1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_9, EMU_SRC_DOCK_MIC_B1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_A, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_B, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_C, EMU_SRC_DOCK_ADC1_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_D, EMU_SRC_DOCK_ADC1_RIGHT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_E, EMU_SRC_DOCK_ADC2_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_F, EMU_SRC_DOCK_ADC2_RIGHT1);
#endif
#if 0
	/* Original */
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_4, EMU_SRC_HANA_ADAT);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_5, EMU_SRC_HANA_ADAT + 1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_6, EMU_SRC_HANA_ADAT + 2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_7, EMU_SRC_HANA_ADAT + 3);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_8, EMU_SRC_HANA_ADAT + 4);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_9, EMU_SRC_HANA_ADAT + 5);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_A, EMU_SRC_HANA_ADAT + 6);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_B, EMU_SRC_HANA_ADAT + 7);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_C, EMU_SRC_DOCK_MIC_A1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_D, EMU_SRC_DOCK_MIC_B1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_E, EMU_SRC_HAMOA_ADC_LEFT2);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE2_EMU32_F, EMU_SRC_HAMOA_ADC_LEFT2);
#endif
	for (i = 0; i < 0x20; i++) {
		/* AudioDock Elink <- Silence */
		snd_emu1010_fpga_link_dst_src_write(emu, 0x0100 + i, EMU_SRC_SILENCE);
	}
	for (i = 0; i < 4; i++) {
		/* Hana SPDIF Out <- Silence */
		snd_emu1010_fpga_link_dst_src_write(emu, 0x0200 + i, EMU_SRC_SILENCE);
	}
	for (i = 0; i < 7; i++) {
		/* Hamoa DAC <- Silence */
		snd_emu1010_fpga_link_dst_src_write(emu, 0x0300 + i, EMU_SRC_SILENCE);
	}
	for (i = 0; i < 7; i++) {
		/* Hana ADAT Out <- Silence */
		snd_emu1010_fpga_link_dst_src_write(emu, EMU_DST_HANA_ADAT + i, EMU_SRC_SILENCE);
	}
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE_I2S0_LEFT, EMU_SRC_DOCK_ADC1_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE_I2S0_RIGHT, EMU_SRC_DOCK_ADC1_RIGHT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE_I2S1_LEFT, EMU_SRC_DOCK_ADC2_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE_I2S1_RIGHT, EMU_SRC_DOCK_ADC2_RIGHT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE_I2S2_LEFT, EMU_SRC_DOCK_ADC3_LEFT1);
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_ALICE_I2S2_RIGHT, EMU_SRC_DOCK_ADC3_RIGHT1);
	snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, 0x01); /* Unmute all */

	snd_emu1010_fpga_read(emu, EMU_HANA_OPTION_CARDS, &tmp);

	/* AC97 1.03, Any 32Meg of 2Gig address, Auto-Mute, EMU32 Slave,
	 * Lock Sound Memory Cache, Lock Tank Memory Cache,
	 * Mute all codecs.
	 */
	outl(0x0000a000, emu->port + HCFG);
	/* AC97 1.03, Any 32Meg of 2Gig address, Auto-Mute, EMU32 Slave,
	 * Lock Sound Memory Cache, Lock Tank Memory Cache,
	 * Un-Mute all codecs.
	 */
	outl(0x0000a001, emu->port + HCFG);

	/* Initial boot complete. Now patches */

	snd_emu1010_fpga_read(emu, EMU_HANA_OPTION_CARDS, &tmp);
	snd_emu1010_fpga_write(emu, EMU_HANA_MIDI_IN, 0x19); /* MIDI Route */
	snd_emu1010_fpga_write(emu, EMU_HANA_MIDI_OUT, 0x0c); /* Unknown */
	snd_emu1010_fpga_write(emu, EMU_HANA_MIDI_IN, 0x19); /* MIDI Route */
	snd_emu1010_fpga_write(emu, EMU_HANA_MIDI_OUT, 0x0c); /* Unknown */
	snd_emu1010_fpga_read(emu, EMU_HANA_SPDIF_MODE, &tmp);
	snd_emu1010_fpga_write(emu, EMU_HANA_SPDIF_MODE, 0x10); /* SPDIF Format spdif  (or 0x11 for aes/ebu) */

#if 0
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_HAMOA_DAC_LEFT1, EMU_SRC_ALICE_EMU32B + 2); /* ALICE2 bus 0xa2 */
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_HAMOA_DAC_RIGHT1, EMU_SRC_ALICE_EMU32B + 3); /* ALICE2 bus 0xa3 */
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_HANA_SPDIF_LEFT1, EMU_SRC_ALICE_EMU32A + 2); /* ALICE2 bus 0xb2 */
	snd_emu1010_fpga_link_dst_src_write(emu,
		EMU_DST_HANA_SPDIF_RIGHT1, EMU_SRC_ALICE_EMU32A + 3); /* ALICE2 bus 0xb3 */
#endif
	/* Default outputs */
	if (emu->card_capabilities->emu_model == EMU_MODEL_EMU1616) {
		/* 1616(M) cardbus default outputs */
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC1_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[0] = 17;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC1_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[1] = 18;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC2_LEFT1, EMU_SRC_ALICE_EMU32A + 2);
		emu->emu1010.output_source[2] = 19;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC2_RIGHT1, EMU_SRC_ALICE_EMU32A + 3);
		emu->emu1010.output_source[3] = 20;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC3_LEFT1, EMU_SRC_ALICE_EMU32A + 4);
		emu->emu1010.output_source[4] = 21;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC3_RIGHT1, EMU_SRC_ALICE_EMU32A + 5);
		emu->emu1010.output_source[5] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_MANA_DAC_LEFT, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[16] = 17;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_MANA_DAC_RIGHT, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[17] = 18;
	} else {
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC1_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[0] = 21;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC1_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[1] = 22;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC2_LEFT1, EMU_SRC_ALICE_EMU32A + 2);
		emu->emu1010.output_source[2] = 23;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC2_RIGHT1, EMU_SRC_ALICE_EMU32A + 3);
		emu->emu1010.output_source[3] = 24;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC3_LEFT1, EMU_SRC_ALICE_EMU32A + 4);
		emu->emu1010.output_source[4] = 25;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC3_RIGHT1, EMU_SRC_ALICE_EMU32A + 5);
		emu->emu1010.output_source[5] = 26;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC4_LEFT1, EMU_SRC_ALICE_EMU32A + 6);
		emu->emu1010.output_source[6] = 27;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_DAC4_RIGHT1, EMU_SRC_ALICE_EMU32A + 7);
		emu->emu1010.output_source[7] = 28;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_PHONES_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[8] = 21;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_PHONES_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[9] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_SPDIF_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[10] = 21;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_DOCK_SPDIF_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[11] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_SPDIF_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[12] = 21;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_SPDIF_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[13] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HAMOA_DAC_LEFT1, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[14] = 21;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HAMOA_DAC_RIGHT1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[15] = 22;
		/* ALICE2 bus 0xa0 */
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_ADAT, EMU_SRC_ALICE_EMU32A + 0);
		emu->emu1010.output_source[16] = 21;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_ADAT + 1, EMU_SRC_ALICE_EMU32A + 1);
		emu->emu1010.output_source[17] = 22;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_ADAT + 2, EMU_SRC_ALICE_EMU32A + 2);
		emu->emu1010.output_source[18] = 23;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_ADAT + 3, EMU_SRC_ALICE_EMU32A + 3);
		emu->emu1010.output_source[19] = 24;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_ADAT + 4, EMU_SRC_ALICE_EMU32A + 4);
		emu->emu1010.output_source[20] = 25;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_ADAT + 5, EMU_SRC_ALICE_EMU32A + 5);
		emu->emu1010.output_source[21] = 26;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_ADAT + 6, EMU_SRC_ALICE_EMU32A + 6);
		emu->emu1010.output_source[22] = 27;
		snd_emu1010_fpga_link_dst_src_write(emu,
			EMU_DST_HANA_ADAT + 7, EMU_SRC_ALICE_EMU32A + 7);
		emu->emu1010.output_source[23] = 28;
	}
	/* TEMP: Select SPDIF in/out */
	/* snd_emu1010_fpga_write(emu, EMU_HANA_OPTICAL_TYPE, 0x0); */ /* Output spdif */

	/* TEMP: Select 48kHz SPDIF out */
	snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, 0x0); /* Mute all */
	snd_emu1010_fpga_write(emu, EMU_HANA_DEFCLOCK, 0x0); /* Default fallback clock 48kHz */
	/* Word Clock source, Internal 48kHz x1 */
	snd_emu1010_fpga_write(emu, EMU_HANA_WCLOCK, EMU_HANA_WCLOCK_INT_48K);
	/* snd_emu1010_fpga_write(emu, EMU_HANA_WCLOCK, EMU_HANA_WCLOCK_INT_48K | EMU_HANA_WCLOCK_4X); */
	emu->emu1010.internal_clock = 1; /* 48000 */
	snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_LEDS_2, 0x12); /* Set LEDs on Audio Dock */
	snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, 0x1); /* Unmute all */
	/* snd_emu1010_fpga_write(emu, 0x7, 0x0); */ /* Mute all */
	/* snd_emu1010_fpga_write(emu, 0x7, 0x1); */ /* Unmute all */
	/* snd_emu1010_fpga_write(emu, 0xe, 0x12); */ /* Set LEDs on Audio Dock */

	return 0;
}
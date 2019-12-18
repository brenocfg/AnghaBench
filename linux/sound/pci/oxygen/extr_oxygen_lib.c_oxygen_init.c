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
struct TYPE_2__ {int function_flags; int misc_flags; int dac_i2s_format; int device_config; int adc_i2s_format; int /*<<< orphan*/  adc_mclks; int /*<<< orphan*/  dac_mclks; int /*<<< orphan*/  dac_volume_min; } ;
struct oxygen {int dac_routing; int dac_mute; int spdif_bits; int spdif_pcm_bits; int has_ac97_0; int has_ac97_1; TYPE_1__ model; scalar_t__ spdif_playback_enable; int /*<<< orphan*/ * dac_volume; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AUX ; 
 int /*<<< orphan*/  AC97_CD ; 
 int /*<<< orphan*/  AC97_CENTER_LFE_MASTER ; 
 int AC97_EA_PRI ; 
 int AC97_EA_PRJ ; 
 int AC97_EA_PRK ; 
 int AC97_EXTENDED_STATUS ; 
 int /*<<< orphan*/  AC97_HEADPHONE ; 
 int /*<<< orphan*/  AC97_LINE ; 
 int /*<<< orphan*/  AC97_MASTER ; 
 int /*<<< orphan*/  AC97_MIC ; 
 int /*<<< orphan*/  AC97_PCM ; 
 int /*<<< orphan*/  AC97_PC_BEEP ; 
 int AC97_PD_PR0 ; 
 int AC97_PD_PR1 ; 
 int AC97_POWERDOWN ; 
 int /*<<< orphan*/  AC97_REC_GAIN ; 
 int /*<<< orphan*/  AC97_REC_SEL ; 
 int /*<<< orphan*/  AC97_RESET ; 
 int /*<<< orphan*/  AC97_SURROUND_MASTER ; 
 int /*<<< orphan*/  AC97_VIDEO ; 
 int CAPTURE_0_FROM_I2S_1 ; 
 int CAPTURE_0_FROM_I2S_2 ; 
 int CAPTURE_1_FROM_SPDIF ; 
 int CAPTURE_2_FROM_I2S_2 ; 
 int CAPTURE_3_FROM_I2S_3 ; 
 int CM9780_BSTSEL ; 
 int CM9780_CBOE ; 
 int CM9780_FROE ; 
 int CM9780_GPIO0IO ; 
 int CM9780_GPIO1IO ; 
 int CM9780_GPIO_SETUP ; 
 int /*<<< orphan*/  CM9780_GPIO_STATUS ; 
 int /*<<< orphan*/  CM9780_GPO0 ; 
 int CM9780_JACK ; 
 int CM9780_LI2LI ; 
 int CM9780_MIC2MIC ; 
 int CM9780_MIX2FR ; 
 int CM9780_MIXER ; 
 int CM9780_PCBSW ; 
 int CM9780_RSOE ; 
 int CM9780_SSOE ; 
 int CM9780_STRO_MIC ; 
 int IEC958_AES1_CON_PCM_CODER ; 
 int /*<<< orphan*/  OXYGEN_2WIRE_BUS_STATUS ; 
 int OXYGEN_2WIRE_INTERRUPT_MASK ; 
 int OXYGEN_2WIRE_LENGTH_8 ; 
 int OXYGEN_2WIRE_SPEED_STANDARD ; 
 int /*<<< orphan*/  OXYGEN_AC97_CLOCK_DISABLE ; 
 int OXYGEN_AC97_CODEC1_SLOT3 ; 
 int OXYGEN_AC97_CODEC1_SLOT4 ; 
 unsigned int OXYGEN_AC97_CODEC_0 ; 
 unsigned int OXYGEN_AC97_CODEC_1 ; 
 int /*<<< orphan*/  OXYGEN_AC97_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_AC97_INTERRUPT_MASK ; 
 int OXYGEN_AC97_INT_READ_DONE ; 
 int OXYGEN_AC97_INT_WRITE_DONE ; 
 int /*<<< orphan*/  OXYGEN_AC97_IN_CONFIG ; 
 int /*<<< orphan*/  OXYGEN_AC97_NO_CODEC_0 ; 
 int /*<<< orphan*/  OXYGEN_AC97_OUT_CONFIG ; 
 int /*<<< orphan*/  OXYGEN_ADC_MONITOR ; 
 int OXYGEN_A_MONITOR_ROUTE_0_SHIFT ; 
 int OXYGEN_A_MONITOR_ROUTE_1_SHIFT ; 
 int OXYGEN_A_MONITOR_ROUTE_2_SHIFT ; 
 int OXYGEN_A_MONITOR_ROUTE_3_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_A_MONITOR_ROUTING ; 
 int OXYGEN_DMA_A_BURST_8 ; 
 int OXYGEN_DMA_MULTICH_BURST_8 ; 
 int /*<<< orphan*/  OXYGEN_DMA_PAUSE ; 
 int /*<<< orphan*/  OXYGEN_DMA_STATUS ; 
 int OXYGEN_FORMAT_16 ; 
 int /*<<< orphan*/  OXYGEN_FUNCTION ; 
 int OXYGEN_FUNCTION_2WIRE_SPI_MASK ; 
 int OXYGEN_FUNCTION_ENABLE_SPI_4_5 ; 
 int OXYGEN_FUNCTION_RESET_CODEC ; 
 int /*<<< orphan*/  OXYGEN_GPIO_INTERRUPT_MASK ; 
 int /*<<< orphan*/  OXYGEN_GPI_INTERRUPT_MASK ; 
 int /*<<< orphan*/  OXYGEN_I2S_A_FORMAT ; 
 int OXYGEN_I2S_BCLK_64 ; 
 int OXYGEN_I2S_BITS_16 ; 
 int /*<<< orphan*/  OXYGEN_I2S_B_FORMAT ; 
 int /*<<< orphan*/  OXYGEN_I2S_C_FORMAT ; 
 int OXYGEN_I2S_MASTER ; 
 int OXYGEN_I2S_MCLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OXYGEN_I2S_MULTICH_FORMAT ; 
 int OXYGEN_I2S_MUTE_MCLK ; 
 int /*<<< orphan*/  OXYGEN_INTERRUPT_MASK ; 
 int /*<<< orphan*/  OXYGEN_MISC ; 
 int OXYGEN_MISC_MIDI ; 
 int /*<<< orphan*/  OXYGEN_MISC_PCI_MEM_W_1_CLOCK ; 
 int OXYGEN_MISC_REC_A_FROM_MULTICH ; 
 int OXYGEN_MISC_REC_B_FROM_AC97 ; 
 int OXYGEN_MISC_REC_C_FROM_SPDIF ; 
 int OXYGEN_MISC_WRITE_PCI_SUBID ; 
 int /*<<< orphan*/  OXYGEN_MPU401_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_MPU401_LOOPBACK ; 
 int OXYGEN_MULTICH_FORMAT_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_PLAY_CHANNELS ; 
 int OXYGEN_PLAY_CHANNELS_2 ; 
 int OXYGEN_PLAY_DAC0_SOURCE_SHIFT ; 
 int OXYGEN_PLAY_DAC1_SOURCE_SHIFT ; 
 int OXYGEN_PLAY_DAC2_SOURCE_SHIFT ; 
 int OXYGEN_PLAY_DAC3_SOURCE_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_PLAY_FORMAT ; 
 int OXYGEN_PLAY_MULTICH_I2S_DAC ; 
 int /*<<< orphan*/  OXYGEN_PLAY_ROUTING ; 
 int OXYGEN_PLAY_SPDIF_SPDIF ; 
 int OXYGEN_RATE_48000 ; 
 int OXYGEN_REC_A_ROUTE_I2S_ADC_1 ; 
 int OXYGEN_REC_B_ROUTE_I2S_ADC_2 ; 
 int /*<<< orphan*/  OXYGEN_REC_CHANNELS ; 
 int OXYGEN_REC_CHANNELS_2_2_2 ; 
 int OXYGEN_REC_C_ROUTE_SPDIF ; 
 int /*<<< orphan*/  OXYGEN_REC_FORMAT ; 
 int OXYGEN_REC_FORMAT_A_SHIFT ; 
 int OXYGEN_REC_FORMAT_B_SHIFT ; 
 int OXYGEN_REC_FORMAT_C_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_REC_ROUTING ; 
 int /*<<< orphan*/  OXYGEN_REVISION ; 
 int OXYGEN_REVISION_2 ; 
 int OXYGEN_SPDIF_C ; 
 int OXYGEN_SPDIF_CATEGORY_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_SPDIF_CONTROL ; 
 int OXYGEN_SPDIF_FORMAT_SHIFT ; 
 int OXYGEN_SPDIF_IN_CLOCK_96 ; 
 int OXYGEN_SPDIF_IN_CLOCK_MASK ; 
 int OXYGEN_SPDIF_LOCK_MASK ; 
 int OXYGEN_SPDIF_LOCK_PAR ; 
 int OXYGEN_SPDIF_LOOPBACK ; 
 int OXYGEN_SPDIF_ORIGINAL ; 
 int /*<<< orphan*/  OXYGEN_SPDIF_OUTPUT_BITS ; 
 int OXYGEN_SPDIF_OUT_ENABLE ; 
 int OXYGEN_SPDIF_RATE_MASK ; 
 int OXYGEN_SPDIF_SENSE_MASK ; 
 int OXYGEN_SPDIF_SENSE_PAR ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  oxygen_ac97_clear_bits (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_ac97_set_bits (struct oxygen*,int,int,int) ; 
 int /*<<< orphan*/  oxygen_clear_bits32 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_clear_bits8 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int oxygen_read16 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_set_bits32 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_set_bits8 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_write32 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_write32_masked (struct oxygen*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  oxygen_write8 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_write8_masked (struct oxygen*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  oxygen_write_ac97 (struct oxygen*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void oxygen_init(struct oxygen *chip)
{
	unsigned int i;

	chip->dac_routing = 1;
	for (i = 0; i < 8; ++i)
		chip->dac_volume[i] = chip->model.dac_volume_min;
	chip->dac_mute = 1;
	chip->spdif_playback_enable = 0;
	chip->spdif_bits = OXYGEN_SPDIF_C | OXYGEN_SPDIF_ORIGINAL |
		(IEC958_AES1_CON_PCM_CODER << OXYGEN_SPDIF_CATEGORY_SHIFT);
	chip->spdif_pcm_bits = chip->spdif_bits;

	if (!(oxygen_read8(chip, OXYGEN_REVISION) & OXYGEN_REVISION_2))
		oxygen_set_bits8(chip, OXYGEN_MISC,
				 OXYGEN_MISC_PCI_MEM_W_1_CLOCK);

	i = oxygen_read16(chip, OXYGEN_AC97_CONTROL);
	chip->has_ac97_0 = (i & OXYGEN_AC97_CODEC_0) != 0;
	chip->has_ac97_1 = (i & OXYGEN_AC97_CODEC_1) != 0;

	oxygen_write8_masked(chip, OXYGEN_FUNCTION,
			     OXYGEN_FUNCTION_RESET_CODEC |
			     chip->model.function_flags,
			     OXYGEN_FUNCTION_RESET_CODEC |
			     OXYGEN_FUNCTION_2WIRE_SPI_MASK |
			     OXYGEN_FUNCTION_ENABLE_SPI_4_5);
	oxygen_write8(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_write8(chip, OXYGEN_DMA_PAUSE, 0);
	oxygen_write8(chip, OXYGEN_PLAY_CHANNELS,
		      OXYGEN_PLAY_CHANNELS_2 |
		      OXYGEN_DMA_A_BURST_8 |
		      OXYGEN_DMA_MULTICH_BURST_8);
	oxygen_write16(chip, OXYGEN_INTERRUPT_MASK, 0);
	oxygen_write8_masked(chip, OXYGEN_MISC,
			     chip->model.misc_flags,
			     OXYGEN_MISC_WRITE_PCI_SUBID |
			     OXYGEN_MISC_REC_C_FROM_SPDIF |
			     OXYGEN_MISC_REC_B_FROM_AC97 |
			     OXYGEN_MISC_REC_A_FROM_MULTICH |
			     OXYGEN_MISC_MIDI);
	oxygen_write8(chip, OXYGEN_REC_FORMAT,
		      (OXYGEN_FORMAT_16 << OXYGEN_REC_FORMAT_A_SHIFT) |
		      (OXYGEN_FORMAT_16 << OXYGEN_REC_FORMAT_B_SHIFT) |
		      (OXYGEN_FORMAT_16 << OXYGEN_REC_FORMAT_C_SHIFT));
	oxygen_write8(chip, OXYGEN_PLAY_FORMAT,
		      (OXYGEN_FORMAT_16 << OXYGEN_SPDIF_FORMAT_SHIFT) |
		      (OXYGEN_FORMAT_16 << OXYGEN_MULTICH_FORMAT_SHIFT));
	oxygen_write8(chip, OXYGEN_REC_CHANNELS, OXYGEN_REC_CHANNELS_2_2_2);
	oxygen_write16(chip, OXYGEN_I2S_MULTICH_FORMAT,
		       OXYGEN_RATE_48000 |
		       chip->model.dac_i2s_format |
		       OXYGEN_I2S_MCLK(chip->model.dac_mclks) |
		       OXYGEN_I2S_BITS_16 |
		       OXYGEN_I2S_MASTER |
		       OXYGEN_I2S_BCLK_64);
	if (chip->model.device_config & CAPTURE_0_FROM_I2S_1)
		oxygen_write16(chip, OXYGEN_I2S_A_FORMAT,
			       OXYGEN_RATE_48000 |
			       chip->model.adc_i2s_format |
			       OXYGEN_I2S_MCLK(chip->model.adc_mclks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_BCLK_64);
	else
		oxygen_write16(chip, OXYGEN_I2S_A_FORMAT,
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_MUTE_MCLK);
	if (chip->model.device_config & (CAPTURE_0_FROM_I2S_2 |
					 CAPTURE_2_FROM_I2S_2))
		oxygen_write16(chip, OXYGEN_I2S_B_FORMAT,
			       OXYGEN_RATE_48000 |
			       chip->model.adc_i2s_format |
			       OXYGEN_I2S_MCLK(chip->model.adc_mclks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_BCLK_64);
	else
		oxygen_write16(chip, OXYGEN_I2S_B_FORMAT,
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_MUTE_MCLK);
	if (chip->model.device_config & CAPTURE_3_FROM_I2S_3)
		oxygen_write16(chip, OXYGEN_I2S_C_FORMAT,
			       OXYGEN_RATE_48000 |
			       chip->model.adc_i2s_format |
			       OXYGEN_I2S_MCLK(chip->model.adc_mclks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_BCLK_64);
	else
		oxygen_write16(chip, OXYGEN_I2S_C_FORMAT,
			       OXYGEN_I2S_MASTER |
			       OXYGEN_I2S_MUTE_MCLK);
	oxygen_clear_bits32(chip, OXYGEN_SPDIF_CONTROL,
			    OXYGEN_SPDIF_OUT_ENABLE |
			    OXYGEN_SPDIF_LOOPBACK);
	if (chip->model.device_config & CAPTURE_1_FROM_SPDIF)
		oxygen_write32_masked(chip, OXYGEN_SPDIF_CONTROL,
				      OXYGEN_SPDIF_SENSE_MASK |
				      OXYGEN_SPDIF_LOCK_MASK |
				      OXYGEN_SPDIF_RATE_MASK |
				      OXYGEN_SPDIF_LOCK_PAR |
				      OXYGEN_SPDIF_IN_CLOCK_96,
				      OXYGEN_SPDIF_SENSE_MASK |
				      OXYGEN_SPDIF_LOCK_MASK |
				      OXYGEN_SPDIF_RATE_MASK |
				      OXYGEN_SPDIF_SENSE_PAR |
				      OXYGEN_SPDIF_LOCK_PAR |
				      OXYGEN_SPDIF_IN_CLOCK_MASK);
	else
		oxygen_clear_bits32(chip, OXYGEN_SPDIF_CONTROL,
				    OXYGEN_SPDIF_SENSE_MASK |
				    OXYGEN_SPDIF_LOCK_MASK |
				    OXYGEN_SPDIF_RATE_MASK);
	oxygen_write32(chip, OXYGEN_SPDIF_OUTPUT_BITS, chip->spdif_bits);
	oxygen_write16(chip, OXYGEN_2WIRE_BUS_STATUS,
		       OXYGEN_2WIRE_LENGTH_8 |
		       OXYGEN_2WIRE_INTERRUPT_MASK |
		       OXYGEN_2WIRE_SPEED_STANDARD);
	oxygen_clear_bits8(chip, OXYGEN_MPU401_CONTROL, OXYGEN_MPU401_LOOPBACK);
	oxygen_write8(chip, OXYGEN_GPI_INTERRUPT_MASK, 0);
	oxygen_write16(chip, OXYGEN_GPIO_INTERRUPT_MASK, 0);
	oxygen_write16(chip, OXYGEN_PLAY_ROUTING,
		       OXYGEN_PLAY_MULTICH_I2S_DAC |
		       OXYGEN_PLAY_SPDIF_SPDIF |
		       (0 << OXYGEN_PLAY_DAC0_SOURCE_SHIFT) |
		       (1 << OXYGEN_PLAY_DAC1_SOURCE_SHIFT) |
		       (2 << OXYGEN_PLAY_DAC2_SOURCE_SHIFT) |
		       (3 << OXYGEN_PLAY_DAC3_SOURCE_SHIFT));
	oxygen_write8(chip, OXYGEN_REC_ROUTING,
		      OXYGEN_REC_A_ROUTE_I2S_ADC_1 |
		      OXYGEN_REC_B_ROUTE_I2S_ADC_2 |
		      OXYGEN_REC_C_ROUTE_SPDIF);
	oxygen_write8(chip, OXYGEN_ADC_MONITOR, 0);
	oxygen_write8(chip, OXYGEN_A_MONITOR_ROUTING,
		      (0 << OXYGEN_A_MONITOR_ROUTE_0_SHIFT) |
		      (1 << OXYGEN_A_MONITOR_ROUTE_1_SHIFT) |
		      (2 << OXYGEN_A_MONITOR_ROUTE_2_SHIFT) |
		      (3 << OXYGEN_A_MONITOR_ROUTE_3_SHIFT));

	if (chip->has_ac97_0 | chip->has_ac97_1)
		oxygen_write8(chip, OXYGEN_AC97_INTERRUPT_MASK,
			      OXYGEN_AC97_INT_READ_DONE |
			      OXYGEN_AC97_INT_WRITE_DONE);
	else
		oxygen_write8(chip, OXYGEN_AC97_INTERRUPT_MASK, 0);
	oxygen_write32(chip, OXYGEN_AC97_OUT_CONFIG, 0);
	oxygen_write32(chip, OXYGEN_AC97_IN_CONFIG, 0);
	if (!(chip->has_ac97_0 | chip->has_ac97_1))
		oxygen_set_bits16(chip, OXYGEN_AC97_CONTROL,
				  OXYGEN_AC97_CLOCK_DISABLE);
	if (!chip->has_ac97_0) {
		oxygen_set_bits16(chip, OXYGEN_AC97_CONTROL,
				  OXYGEN_AC97_NO_CODEC_0);
	} else {
		oxygen_write_ac97(chip, 0, AC97_RESET, 0);
		msleep(1);
		oxygen_ac97_set_bits(chip, 0, CM9780_GPIO_SETUP,
				     CM9780_GPIO0IO | CM9780_GPIO1IO);
		oxygen_ac97_set_bits(chip, 0, CM9780_MIXER,
				     CM9780_BSTSEL | CM9780_STRO_MIC |
				     CM9780_MIX2FR | CM9780_PCBSW);
		oxygen_ac97_set_bits(chip, 0, CM9780_JACK,
				     CM9780_RSOE | CM9780_CBOE |
				     CM9780_SSOE | CM9780_FROE |
				     CM9780_MIC2MIC | CM9780_LI2LI);
		oxygen_write_ac97(chip, 0, AC97_MASTER, 0x0000);
		oxygen_write_ac97(chip, 0, AC97_PC_BEEP, 0x8000);
		oxygen_write_ac97(chip, 0, AC97_MIC, 0x8808);
		oxygen_write_ac97(chip, 0, AC97_LINE, 0x0808);
		oxygen_write_ac97(chip, 0, AC97_CD, 0x8808);
		oxygen_write_ac97(chip, 0, AC97_VIDEO, 0x8808);
		oxygen_write_ac97(chip, 0, AC97_AUX, 0x8808);
		oxygen_write_ac97(chip, 0, AC97_REC_GAIN, 0x8000);
		oxygen_write_ac97(chip, 0, AC97_CENTER_LFE_MASTER, 0x8080);
		oxygen_write_ac97(chip, 0, AC97_SURROUND_MASTER, 0x8080);
		oxygen_ac97_clear_bits(chip, 0, CM9780_GPIO_STATUS,
				       CM9780_GPO0);
		/* power down unused ADCs and DACs */
		oxygen_ac97_set_bits(chip, 0, AC97_POWERDOWN,
				     AC97_PD_PR0 | AC97_PD_PR1);
		oxygen_ac97_set_bits(chip, 0, AC97_EXTENDED_STATUS,
				     AC97_EA_PRI | AC97_EA_PRJ | AC97_EA_PRK);
	}
	if (chip->has_ac97_1) {
		oxygen_set_bits32(chip, OXYGEN_AC97_OUT_CONFIG,
				  OXYGEN_AC97_CODEC1_SLOT3 |
				  OXYGEN_AC97_CODEC1_SLOT4);
		oxygen_write_ac97(chip, 1, AC97_RESET, 0);
		msleep(1);
		oxygen_write_ac97(chip, 1, AC97_MASTER, 0x0000);
		oxygen_write_ac97(chip, 1, AC97_HEADPHONE, 0x8000);
		oxygen_write_ac97(chip, 1, AC97_PC_BEEP, 0x8000);
		oxygen_write_ac97(chip, 1, AC97_MIC, 0x8808);
		oxygen_write_ac97(chip, 1, AC97_LINE, 0x8808);
		oxygen_write_ac97(chip, 1, AC97_CD, 0x8808);
		oxygen_write_ac97(chip, 1, AC97_VIDEO, 0x8808);
		oxygen_write_ac97(chip, 1, AC97_AUX, 0x8808);
		oxygen_write_ac97(chip, 1, AC97_PCM, 0x0808);
		oxygen_write_ac97(chip, 1, AC97_REC_SEL, 0x0000);
		oxygen_write_ac97(chip, 1, AC97_REC_GAIN, 0x0000);
		oxygen_ac97_set_bits(chip, 1, 0x6a, 0x0040);
	}
}
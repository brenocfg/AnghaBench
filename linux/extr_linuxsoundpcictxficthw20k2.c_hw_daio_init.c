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
typedef  int u32 ;
struct hw {scalar_t__ model; TYPE_1__* card; } ;
struct daio_conf {int msr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AUDIO_IO_MCLK ; 
 scalar_t__ AUDIO_IO_RX_BLRCLK ; 
 scalar_t__ AUDIO_IO_RX_CTL ; 
 scalar_t__ AUDIO_IO_TX_BLRCLK ; 
 scalar_t__ AUDIO_IO_TX_CSTAT_H ; 
 scalar_t__ AUDIO_IO_TX_CSTAT_L ; 
 scalar_t__ AUDIO_IO_TX_CTL ; 
 scalar_t__ CTSB1270 ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,scalar_t__,int) ; 

__attribute__((used)) static int hw_daio_init(struct hw *hw, const struct daio_conf *info)
{
	u32 data;
	int i;

	/* Program I2S with proper sample rate and enable the correct I2S
	 * channel. ED(0/8/16/24): Enable all I2S/I2X master clock output */
	if (1 == info->msr) {
		hw_write_20kx(hw, AUDIO_IO_MCLK, 0x01010101);
		hw_write_20kx(hw, AUDIO_IO_TX_BLRCLK, 0x01010101);
		hw_write_20kx(hw, AUDIO_IO_RX_BLRCLK, 0);
	} else if (2 == info->msr) {
		if (hw->model != CTSB1270) {
			hw_write_20kx(hw, AUDIO_IO_MCLK, 0x11111111);
		} else {
			/* PCM4220 on Titanium HD is different. */
			hw_write_20kx(hw, AUDIO_IO_MCLK, 0x11011111);
		}
		/* Specify all playing 96khz
		 * EA [0]	- Enabled
		 * RTA [4:5]	- 96kHz
		 * EB [8]	- Enabled
		 * RTB [12:13]	- 96kHz
		 * EC [16]	- Enabled
		 * RTC [20:21]	- 96kHz
		 * ED [24]	- Enabled
		 * RTD [28:29]	- 96kHz */
		hw_write_20kx(hw, AUDIO_IO_TX_BLRCLK, 0x11111111);
		hw_write_20kx(hw, AUDIO_IO_RX_BLRCLK, 0);
	} else if ((4 == info->msr) && (hw->model == CTSB1270)) {
		hw_write_20kx(hw, AUDIO_IO_MCLK, 0x21011111);
		hw_write_20kx(hw, AUDIO_IO_TX_BLRCLK, 0x21212121);
		hw_write_20kx(hw, AUDIO_IO_RX_BLRCLK, 0);
	} else {
		dev_alert(hw->card->dev,
			  "ERROR!!! Invalid sampling rate!!!\n");
		return -EINVAL;
	}

	for (i = 0; i < 8; i++) {
		if (i <= 3) {
			/* This comment looks wrong since loop is over 4  */
			/* channels and emu20k2 supports 4 spdif IOs.     */
			/* 1st 3 channels are SPDIFs (SB0960) */
			if (i == 3)
				data = 0x1001001;
			else
				data = 0x1000001;

			hw_write_20kx(hw, (AUDIO_IO_TX_CTL+(0x40*i)), data);
			hw_write_20kx(hw, (AUDIO_IO_RX_CTL+(0x40*i)), data);

			/* Initialize the SPDIF Out Channel status registers.
			 * The value specified here is based on the typical
			 * values provided in the specification, namely: Clock
			 * Accuracy of 1000ppm, Sample Rate of 48KHz,
			 * unspecified source number, Generation status = 1,
			 * Category code = 0x12 (Digital Signal Mixer),
			 * Mode = 0, Emph = 0, Copy Permitted, AN = 0
			 * (indicating that we're transmitting digital audio,
			 * and the Professional Use bit is 0. */

			hw_write_20kx(hw, AUDIO_IO_TX_CSTAT_L+(0x40*i),
					0x02109204); /* Default to 48kHz */

			hw_write_20kx(hw, AUDIO_IO_TX_CSTAT_H+(0x40*i), 0x0B);
		} else {
			/* Again, loop is over 4 channels not 5. */
			/* Next 5 channels are I2S (SB0960) */
			data = 0x11;
			hw_write_20kx(hw, AUDIO_IO_RX_CTL+(0x40*i), data);
			if (2 == info->msr) {
				/* Four channels per sample period */
				data |= 0x1000;
			} else if (4 == info->msr) {
				/* FIXME: check this against the chip spec */
				data |= 0x2000;
			}
			hw_write_20kx(hw, AUDIO_IO_TX_CTL+(0x40*i), data);
		}
	}

	return 0;
}
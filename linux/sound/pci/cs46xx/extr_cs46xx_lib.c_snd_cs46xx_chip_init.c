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
struct snd_cs46xx {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ACCTL_ESYN ; 
 int ACCTL_RSTN ; 
 int ACCTL_VFRM ; 
 int ACISV_ISV3 ; 
 int ACISV_ISV4 ; 
 int ACOSV_SLV3 ; 
 int ACOSV_SLV4 ; 
 int ACSTS_CRDY ; 
 int /*<<< orphan*/  BA0_ACCTL ; 
 int /*<<< orphan*/  BA0_ACCTL2 ; 
 int /*<<< orphan*/  BA0_ACISV ; 
 int /*<<< orphan*/  BA0_ACOSV ; 
 int /*<<< orphan*/  BA0_ACSTS ; 
 int /*<<< orphan*/  BA0_ACSTS2 ; 
 int /*<<< orphan*/  BA0_CLKCR1 ; 
 int /*<<< orphan*/  BA0_CLKCR2 ; 
 int /*<<< orphan*/  BA0_PLLCC ; 
 int /*<<< orphan*/  BA0_PLLM ; 
 int /*<<< orphan*/  BA0_SERACC ; 
 int /*<<< orphan*/  BA0_SERBCF ; 
 int /*<<< orphan*/  BA0_SERC1 ; 
 int /*<<< orphan*/  BA0_SERC2 ; 
 int /*<<< orphan*/  BA0_SERC3 ; 
 int /*<<< orphan*/  BA0_SERC4 ; 
 int /*<<< orphan*/  BA0_SERC5 ; 
 int /*<<< orphan*/  BA0_SERC6 ; 
 int /*<<< orphan*/  BA0_SERC7 ; 
 int /*<<< orphan*/  BA0_SERMC1 ; 
 int CLKCR1_PLLP ; 
 int CLKCR1_SWCE ; 
 int CLKCR2_PDIVS_8 ; 
 int EIO ; 
 int PLLCC_CDR_73_104_MHZ ; 
 int PLLCC_LPF_1050_2780_KHZ ; 
 int SERACC_CHIP_TYPE_1_03 ; 
 int SERACC_CHIP_TYPE_2_0 ; 
 int SERACC_HSP ; 
 int SERACC_TWO_CODECS ; 
 int SERBCF_HBP ; 
 int SERC1_SO1EN ; 
 int SERC1_SO1F_AC97 ; 
 int SERC2_SI1F_AC97 ; 
 int SERC7_ASDI2EN ; 
 int SERMC1_MSPE ; 
 int SERMC1_PTC_AC97 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_cs46xx_clear_serial_FIFOs (struct snd_cs46xx*) ; 
 int snd_cs46xx_peekBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_cs46xx_chip_init(struct snd_cs46xx *chip)
{
	int timeout;

	/* 
	 *  First, blast the clock control register to zero so that the PLL starts
         *  out in a known state, and blast the master serial port control register
         *  to zero so that the serial ports also start out in a known state.
         */
        snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, 0);
        snd_cs46xx_pokeBA0(chip, BA0_SERMC1, 0);

	/*
	 *  If we are in AC97 mode, then we must set the part to a host controlled
         *  AC-link.  Otherwise, we won't be able to bring up the link.
         */        
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_SERACC, SERACC_HSP | SERACC_CHIP_TYPE_2_0 | 
			   SERACC_TWO_CODECS);	/* 2.00 dual codecs */
	/* snd_cs46xx_pokeBA0(chip, BA0_SERACC, SERACC_HSP | SERACC_CHIP_TYPE_2_0); */ /* 2.00 codec */
#else
	snd_cs46xx_pokeBA0(chip, BA0_SERACC, SERACC_HSP | SERACC_CHIP_TYPE_1_03); /* 1.03 codec */
#endif

        /*
         *  Drive the ARST# pin low for a minimum of 1uS (as defined in the AC97
         *  spec) and then drive it high.  This is done for non AC97 modes since
         *  there might be logic external to the CS461x that uses the ARST# line
         *  for a reset.
         */
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL, 0);
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL2, 0);
#endif
	udelay(50);
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_RSTN);
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL2, ACCTL_RSTN);
#endif
    
	/*
	 *  The first thing we do here is to enable sync generation.  As soon
	 *  as we start receiving bit clock, we'll start producing the SYNC
	 *  signal.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_ESYN | ACCTL_RSTN);
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL2, ACCTL_ESYN | ACCTL_RSTN);
#endif

	/*
	 *  Now wait for a short while to allow the AC97 part to start
	 *  generating bit clock (so we don't try to start the PLL without an
	 *  input clock).
	 */
	mdelay(10);

	/*
	 *  Set the serial port timing configuration, so that
	 *  the clock control circuit gets its clock from the correct place.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_SERMC1, SERMC1_PTC_AC97);

	/*
	 *  Write the selected clock control setup to the hardware.  Do not turn on
	 *  SWCE yet (if requested), so that the devices clocked by the output of
	 *  PLL are not clocked until the PLL is stable.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_PLLCC, PLLCC_LPF_1050_2780_KHZ | PLLCC_CDR_73_104_MHZ);
	snd_cs46xx_pokeBA0(chip, BA0_PLLM, 0x3a);
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR2, CLKCR2_PDIVS_8);

	/*
	 *  Power up the PLL.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, CLKCR1_PLLP);

	/*
         *  Wait until the PLL has stabilized.
	 */
	msleep(100);

	/*
	 *  Turn on clocking of the core so that we can setup the serial ports.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, CLKCR1_PLLP | CLKCR1_SWCE);

	/*
	 * Enable FIFO  Host Bypass
	 */
	snd_cs46xx_pokeBA0(chip, BA0_SERBCF, SERBCF_HBP);

	/*
	 *  Fill the serial port FIFOs with silence.
	 */
	snd_cs46xx_clear_serial_FIFOs(chip);

	/*
	 *  Set the serial port FIFO pointer to the first sample in the FIFO.
	 */
	/* snd_cs46xx_pokeBA0(chip, BA0_SERBSP, 0); */

	/*
	 *  Write the serial port configuration to the part.  The master
	 *  enable bit is not set until all other values have been written.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_SERC1, SERC1_SO1F_AC97 | SERC1_SO1EN);
	snd_cs46xx_pokeBA0(chip, BA0_SERC2, SERC2_SI1F_AC97 | SERC1_SO1EN);
	snd_cs46xx_pokeBA0(chip, BA0_SERMC1, SERMC1_PTC_AC97 | SERMC1_MSPE);


#ifdef CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_SERC7, SERC7_ASDI2EN);
	snd_cs46xx_pokeBA0(chip, BA0_SERC3, 0);
	snd_cs46xx_pokeBA0(chip, BA0_SERC4, 0);
	snd_cs46xx_pokeBA0(chip, BA0_SERC5, 0);
	snd_cs46xx_pokeBA0(chip, BA0_SERC6, 1);
#endif

	mdelay(5);


	/*
	 * Wait for the codec ready signal from the AC97 codec.
	 */
	timeout = 150;
	while (timeout-- > 0) {
		/*
		 *  Read the AC97 status register to see if we've seen a CODEC READY
		 *  signal from the AC97 codec.
		 */
		if (snd_cs46xx_peekBA0(chip, BA0_ACSTS) & ACSTS_CRDY)
			goto ok1;
		msleep(10);
	}


	dev_err(chip->card->dev,
		"create - never read codec ready from AC'97\n");
	dev_err(chip->card->dev,
		"it is not probably bug, try to use CS4236 driver\n");
	return -EIO;
 ok1:
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	{
		int count;
		for (count = 0; count < 150; count++) {
			/* First, we want to wait for a short time. */
			udelay(25);
        
			if (snd_cs46xx_peekBA0(chip, BA0_ACSTS2) & ACSTS_CRDY)
				break;
		}

		/*
		 *  Make sure CODEC is READY.
		 */
		if (!(snd_cs46xx_peekBA0(chip, BA0_ACSTS2) & ACSTS_CRDY))
			dev_dbg(chip->card->dev,
				"never read card ready from secondary AC'97\n");
	}
#endif

	/*
	 *  Assert the vaid frame signal so that we can start sending commands
	 *  to the AC97 codec.
	 */
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL, ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);
#ifdef CONFIG_SND_CS46XX_NEW_DSP
	snd_cs46xx_pokeBA0(chip, BA0_ACCTL2, ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);
#endif


	/*
	 *  Wait until we've sampled input slots 3 and 4 as valid, meaning that
	 *  the codec is pumping ADC data across the AC-link.
	 */
	timeout = 150;
	while (timeout-- > 0) {
		/*
		 *  Read the input slot valid register and see if input slots 3 and
		 *  4 are valid yet.
		 */
		if ((snd_cs46xx_peekBA0(chip, BA0_ACISV) & (ACISV_ISV3 | ACISV_ISV4)) == (ACISV_ISV3 | ACISV_ISV4))
			goto ok2;
		msleep(10);
	}

#ifndef CONFIG_SND_CS46XX_NEW_DSP
	dev_err(chip->card->dev,
		"create - never read ISV3 & ISV4 from AC'97\n");
	return -EIO;
#else
	/* This may happen on a cold boot with a Terratec SiXPack 5.1.
	   Reloading the driver may help, if there's other soundcards 
	   with the same problem I would like to know. (Benny) */

	dev_err(chip->card->dev, "never read ISV3 & ISV4 from AC'97\n");
	dev_err(chip->card->dev,
		"Try reloading the ALSA driver, if you find something\n");
	dev_err(chip->card->dev,
		"broken or not working on your soundcard upon\n");
	dev_err(chip->card->dev,
		"this message please report to alsa-devel@alsa-project.org\n");

	return -EIO;
#endif
 ok2:

	/*
	 *  Now, assert valid frame and the slot 3 and 4 valid bits.  This will
	 *  commense the transfer of digital audio data to the AC97 codec.
	 */

	snd_cs46xx_pokeBA0(chip, BA0_ACOSV, ACOSV_SLV3 | ACOSV_SLV4);


	/*
	 *  Power down the DAC and ADC.  We will power them up (if) when we need
	 *  them.
	 */
	/* snd_cs46xx_pokeBA0(chip, BA0_AC97_POWERDOWN, 0x300); */

	/*
	 *  Turn off the Processor by turning off the software clock enable flag in 
	 *  the clock control register.
	 */
	/* tmp = snd_cs46xx_peekBA0(chip, BA0_CLKCR1) & ~CLKCR1_SWCE; */
	/* snd_cs46xx_pokeBA0(chip, BA0_CLKCR1, tmp); */

	return 0;
}
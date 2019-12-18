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
struct es1938 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ESSSB_IREG_AUDIO2MODE ; 
 int /*<<< orphan*/  ESS_CMD_DMATYPE ; 
 int /*<<< orphan*/  ESS_CMD_DRQCONTROL ; 
 int /*<<< orphan*/  ESS_CMD_ENABLEAUDIO1 ; 
 int /*<<< orphan*/  ESS_CMD_ENABLEEXT ; 
 int /*<<< orphan*/  ESS_CMD_IRQCONTROL ; 
 int /*<<< orphan*/  READDATA ; 
 int /*<<< orphan*/  RESET ; 
 int RESET_LOOP_TIMEOUT ; 
 int /*<<< orphan*/  SLSB_REG (struct es1938*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1938_bits (struct es1938*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_es1938_mixer_write (struct es1938*,int,int) ; 
 int /*<<< orphan*/  snd_es1938_write (struct es1938*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_es1938_write_cmd (struct es1938*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_es1938_reset(struct es1938 *chip)
{
	int i;

	outb(3, SLSB_REG(chip, RESET));
	inb(SLSB_REG(chip, RESET));
	outb(0, SLSB_REG(chip, RESET));
	for (i = 0; i < RESET_LOOP_TIMEOUT; i++) {
		if (inb(SLSB_REG(chip, STATUS)) & 0x80) {
			if (inb(SLSB_REG(chip, READDATA)) == 0xaa)
				goto __next;
		}
	}
	dev_err(chip->card->dev, "ESS Solo-1 reset failed\n");

     __next:
	snd_es1938_write_cmd(chip, ESS_CMD_ENABLEEXT);

	/* Demand transfer DMA: 4 bytes per DMA request */
	snd_es1938_write(chip, ESS_CMD_DMATYPE, 2);

	/* Change behaviour of register A1
	   4x oversampling
	   2nd channel DAC asynchronous */                                                      
	snd_es1938_mixer_write(chip, ESSSB_IREG_AUDIO2MODE, 0x32);
	/* enable/select DMA channel and IRQ channel */
	snd_es1938_bits(chip, ESS_CMD_IRQCONTROL, 0xf0, 0x50);
	snd_es1938_bits(chip, ESS_CMD_DRQCONTROL, 0xf0, 0x50);
	snd_es1938_write_cmd(chip, ESS_CMD_ENABLEAUDIO1);
	/* Set spatializer parameters to recommended values */
	snd_es1938_mixer_write(chip, 0x54, 0x8f);
	snd_es1938_mixer_write(chip, 0x56, 0x95);
	snd_es1938_mixer_write(chip, 0x58, 0x94);
	snd_es1938_mixer_write(chip, 0x5a, 0x80);
}
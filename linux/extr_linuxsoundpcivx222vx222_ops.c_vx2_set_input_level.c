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
struct snd_vx222 {int mic_level; int regSELMIC; scalar_t__* input_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int MICRO_SELECT_PREAMPLI_MASK ; 
 int MICRO_SELECT_PREAMPLI_OFFSET ; 
 int /*<<< orphan*/  RUER ; 
 int /*<<< orphan*/  SELMIC ; 
 scalar_t__ V2_MICRO_LEVEL_RANGE ; 
 int VX_DATA_CODEC_MASK ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  vx_inl (struct snd_vx222*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outl (struct snd_vx222*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vx2_set_input_level(struct snd_vx222 *chip)
{
	int i, miclevel, preamp;
	unsigned int data;

	miclevel = chip->mic_level;
	miclevel += V2_MICRO_LEVEL_RANGE; /* add 318 - 0xff */
	preamp = 0;
        while (miclevel > 210) { /* limitation to +9dB of 3310 real gain */
		preamp++;	/* raise pre ampli + 18dB */
		miclevel -= (18 * 2);   /* lower level 18 dB (*2 because of 0.5 dB steps !) */
        }
	if (snd_BUG_ON(preamp >= 4))
		return;

	/* set pre-amp level */
	chip->regSELMIC &= ~MICRO_SELECT_PREAMPLI_MASK;
	chip->regSELMIC |= (preamp << MICRO_SELECT_PREAMPLI_OFFSET) & MICRO_SELECT_PREAMPLI_MASK;
	vx_outl(chip, SELMIC, chip->regSELMIC);

	data = (unsigned int)miclevel << 16 |
		(unsigned int)chip->input_level[1] << 8 |
		(unsigned int)chip->input_level[0];
	vx_inl(chip, DATA); /* Activate input level programming */

	/* We have to send 32 bits (4 x 8 bits) */
	for (i = 0; i < 32; i++, data <<= 1)
		vx_outl(chip, DATA, ((data & 0x80000000) ? VX_DATA_CODEC_MASK : 0));

	vx_inl(chip, RUER); /* Terminate input level programming */
}
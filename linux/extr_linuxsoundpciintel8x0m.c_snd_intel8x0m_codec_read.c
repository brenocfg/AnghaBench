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
struct snd_ac97 {int num; struct intel8x0m* private_data; } ;
struct intel8x0m {TYPE_1__* card; int /*<<< orphan*/  in_ac97_init; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short AC97_GPIO_STATUS ; 
 int /*<<< orphan*/  GLOB_STA ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 unsigned int ICH_GSCI ; 
 unsigned int ICH_PRI ; 
 unsigned int ICH_RCS ; 
 unsigned int ICH_SRI ; 
 unsigned int ICH_TRI ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned short) ; 
 unsigned short iagetword (struct intel8x0m*,unsigned short) ; 
 unsigned int igetdword (struct intel8x0m*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0m*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ snd_intel8x0m_codec_semaphore (struct intel8x0m*,int) ; 

__attribute__((used)) static unsigned short snd_intel8x0m_codec_read(struct snd_ac97 *ac97,
					       unsigned short reg)
{
	struct intel8x0m *chip = ac97->private_data;
	unsigned short res;
	unsigned int tmp;

	if (snd_intel8x0m_codec_semaphore(chip, ac97->num) < 0) {
		if (! chip->in_ac97_init)
			dev_err(chip->card->dev,
				"codec_read %d: semaphore is not ready for register 0x%x\n",
				ac97->num, reg);
		res = 0xffff;
	} else {
		res = iagetword(chip, reg + ac97->num * 0x80);
		if ((tmp = igetdword(chip, ICHREG(GLOB_STA))) & ICH_RCS) {
			/* reset RCS and preserve other R/WC bits */
			iputdword(chip, ICHREG(GLOB_STA),
				  tmp & ~(ICH_SRI|ICH_PRI|ICH_TRI|ICH_GSCI));
			if (! chip->in_ac97_init)
				dev_err(chip->card->dev,
					"codec_read %d: read timeout for register 0x%x\n",
					ac97->num, reg);
			res = 0xffff;
		}
	}
	if (reg == AC97_GPIO_STATUS)
		iagetword(chip, 0); /* clear semaphore */
	return res;
}
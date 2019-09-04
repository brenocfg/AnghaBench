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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned short) ; 
 int /*<<< orphan*/  iaputword (struct intel8x0m*,unsigned short,unsigned short) ; 
 scalar_t__ snd_intel8x0m_codec_semaphore (struct intel8x0m*,int) ; 

__attribute__((used)) static void snd_intel8x0m_codec_write(struct snd_ac97 *ac97,
				      unsigned short reg,
				      unsigned short val)
{
	struct intel8x0m *chip = ac97->private_data;
	
	if (snd_intel8x0m_codec_semaphore(chip, ac97->num) < 0) {
		if (! chip->in_ac97_init)
			dev_err(chip->card->dev,
				"codec_write %d: semaphore is not ready for register 0x%x\n",
				ac97->num, reg);
	}
	iaputword(chip, reg + ac97->num * 0x80, val);
}
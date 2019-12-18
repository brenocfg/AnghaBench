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
struct snd_ac97 {unsigned short addr; int /*<<< orphan*/  num; struct fm801* private_data; } ;
struct fm801 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CMD ; 
 int /*<<< orphan*/  AC97_DATA ; 
 unsigned short FM801_AC97_ADDR_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fm801_ac97_is_ready (struct fm801*,int) ; 
 int /*<<< orphan*/  fm801_writew (struct fm801*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void snd_fm801_codec_write(struct snd_ac97 *ac97,
				  unsigned short reg,
				  unsigned short val)
{
	struct fm801 *chip = ac97->private_data;

	/*
	 *  Wait until the codec interface is not ready..
	 */
	if (!fm801_ac97_is_ready(chip, 100)) {
		dev_err(chip->card->dev, "AC'97 interface is busy (1)\n");
		return;
	}

	/* write data and address */
	fm801_writew(chip, AC97_DATA, val);
	fm801_writew(chip, AC97_CMD, reg | (ac97->addr << FM801_AC97_ADDR_SHIFT));
	/*
	 *  Wait until the write command is not completed..
	 */
	if (!fm801_ac97_is_ready(chip, 1000))
		dev_err(chip->card->dev, "AC'97 interface #%d is busy (2)\n",
		ac97->num);
}
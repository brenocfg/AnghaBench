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
struct intel8x0 {TYPE_1__* card; int /*<<< orphan*/  in_ac97_init; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_CSPSR ; 
 int EBUSY ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int igetbyte (struct intel8x0*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_intel8x0_ali_codec_ready(struct intel8x0 *chip, int mask)
{
	int count = 0;
	for (count = 0; count < 0x7f; count++) {
		int val = igetbyte(chip, ICHREG(ALI_CSPSR));
		if (val & mask)
			return 0;
	}
	if (! chip->in_ac97_init)
		dev_warn(chip->card->dev, "AC97 codec ready timeout.\n");
	return -EBUSY;
}
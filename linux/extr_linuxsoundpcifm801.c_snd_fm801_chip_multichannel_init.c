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
struct fm801 {int secondary_addr; int secondary; scalar_t__ multichannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_DATA ; 
 int /*<<< orphan*/  AC97_VENDOR_ID1 ; 
 unsigned short fm801_readw (struct fm801*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_for_codec (struct fm801*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_fm801_chip_multichannel_init(struct fm801 *chip)
{
	unsigned short cmdw;

	if (chip->multichannel) {
		if (chip->secondary_addr) {
			wait_for_codec(chip, chip->secondary_addr,
				       AC97_VENDOR_ID1, msecs_to_jiffies(50));
		} else {
			/* my card has the secondary codec */
			/* at address #3, so the loop is inverted */
			int i;
			for (i = 3; i > 0; i--) {
				if (!wait_for_codec(chip, i, AC97_VENDOR_ID1,
						     msecs_to_jiffies(50))) {
					cmdw = fm801_readw(chip, AC97_DATA);
					if (cmdw != 0xffff && cmdw != 0) {
						chip->secondary = 1;
						chip->secondary_addr = i;
						break;
					}
				}
			}
		}

		/* the recovery phase, it seems that probing for non-existing codec might */
		/* cause timeout problems */
		wait_for_codec(chip, 0, AC97_VENDOR_ID1, msecs_to_jiffies(750));
	}
}
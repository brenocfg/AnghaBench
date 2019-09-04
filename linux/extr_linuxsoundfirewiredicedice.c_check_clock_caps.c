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
struct snd_dice {int clock_caps; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CLOCK_CAP_RATE_44100 ; 
 int CLOCK_CAP_RATE_48000 ; 
 int CLOCK_CAP_SOURCE_ARX1 ; 
 int CLOCK_CAP_SOURCE_INTERNAL ; 
 int /*<<< orphan*/  GLOBAL_CLOCK_CAPABILITIES ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_dice_transaction_read_global (struct snd_dice*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int check_clock_caps(struct snd_dice *dice)
{
	__be32 value;
	int err;

	/* some very old firmwares don't tell about their clock support */
	if (dice->clock_caps > 0) {
		err = snd_dice_transaction_read_global(dice,
						GLOBAL_CLOCK_CAPABILITIES,
						&value, 4);
		if (err < 0)
			return err;
		dice->clock_caps = be32_to_cpu(value);
	} else {
		/* this should be supported by any device */
		dice->clock_caps = CLOCK_CAP_RATE_44100 |
				   CLOCK_CAP_RATE_48000 |
				   CLOCK_CAP_SOURCE_ARX1 |
				   CLOCK_CAP_SOURCE_INTERNAL;
	}

	return 0;
}
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
struct snd_dice {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int CLOCK_RATE_MASK ; 
 unsigned int CLOCK_RATE_SHIFT ; 
 int ENOSYS ; 
 unsigned int SND_DICE_RATES_COUNT ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int get_clock_info (struct snd_dice*,int /*<<< orphan*/ *) ; 
 unsigned int* snd_dice_rates ; 

int snd_dice_transaction_get_rate(struct snd_dice *dice, unsigned int *rate)
{
	__be32 info;
	unsigned int index;
	int err;

	err = get_clock_info(dice, &info);
	if (err < 0)
		goto end;

	index = (be32_to_cpu(info) & CLOCK_RATE_MASK) >> CLOCK_RATE_SHIFT;
	if (index >= SND_DICE_RATES_COUNT) {
		err = -ENOSYS;
		goto end;
	}

	*rate = snd_dice_rates[index];
end:
	return err;
}
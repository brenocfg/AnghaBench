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
typedef  int u32 ;
struct snd_dice {int /*<<< orphan*/  clock_accepted; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  nominal ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int CLOCK_RATE_MASK ; 
 int CLOCK_RATE_SHIFT ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GLOBAL_CLOCK_SELECT ; 
 int /*<<< orphan*/  GLOBAL_STATUS ; 
 int /*<<< orphan*/  NOTIFICATION_TIMEOUT_MS ; 
 int STATUS_SOURCE_LOCKED ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned int* snd_dice_rates ; 
 int snd_dice_transaction_read_global (struct snd_dice*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_dice_transaction_write_global (struct snd_dice*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ensure_phase_lock(struct snd_dice *dice, unsigned int rate)
{
	__be32 reg, nominal;
	u32 data;
	int i;
	int err;

	err = snd_dice_transaction_read_global(dice, GLOBAL_CLOCK_SELECT,
					       &reg, sizeof(reg));
	if (err < 0)
		return err;

	data = be32_to_cpu(reg);

	data &= ~CLOCK_RATE_MASK;
	for (i = 0; i < ARRAY_SIZE(snd_dice_rates); ++i) {
		if (snd_dice_rates[i] == rate)
			break;
	}
	if (i == ARRAY_SIZE(snd_dice_rates))
		return -EINVAL;
	data |= i << CLOCK_RATE_SHIFT;

	if (completion_done(&dice->clock_accepted))
		reinit_completion(&dice->clock_accepted);

	reg = cpu_to_be32(data);
	err = snd_dice_transaction_write_global(dice, GLOBAL_CLOCK_SELECT,
						&reg, sizeof(reg));
	if (err < 0)
		return err;

	if (wait_for_completion_timeout(&dice->clock_accepted,
			msecs_to_jiffies(NOTIFICATION_TIMEOUT_MS)) == 0) {
		/*
		 * Old versions of Dice firmware transfer no notification when
		 * the same clock status as current one is set. In this case,
		 * just check current clock status.
		 */
		err = snd_dice_transaction_read_global(dice, GLOBAL_STATUS,
						&nominal, sizeof(nominal));
		if (err < 0)
			return err;
		if (!(be32_to_cpu(nominal) & STATUS_SOURCE_LOCKED))
			return -ETIMEDOUT;
	}

	return 0;
}
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
struct snd_msnd {int mode; int /*<<< orphan*/  flags; int /*<<< orphan*/  play_period_bytes; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  F_WRITEFLUSH ; 
 int /*<<< orphan*/  F_WRITING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_play_delay_jiffies (struct snd_msnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_msnd_dsp_write_flush(struct snd_msnd *chip)
{
	if (!(chip->mode & FMODE_WRITE) || !test_bit(F_WRITING, &chip->flags))
		return;
	set_bit(F_WRITEFLUSH, &chip->flags);
/*	interruptible_sleep_on_timeout(
		&chip->writeflush,
		get_play_delay_jiffies(&chip, chip->DAPF.len));*/
	clear_bit(F_WRITEFLUSH, &chip->flags);
	if (!signal_pending(current))
		schedule_timeout_interruptible(
			get_play_delay_jiffies(chip, chip->play_period_bytes));
	clear_bit(F_WRITING, &chip->flags);
}
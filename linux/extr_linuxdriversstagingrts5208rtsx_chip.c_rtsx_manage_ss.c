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
struct rtsx_chip {int ss_counter; int ss_idle_period; scalar_t__ sd_io; } ;

/* Variables and functions */
 int POLLING_INTERVAL ; 
 scalar_t__ RTSX_STAT_IDLE ; 
 int /*<<< orphan*/  rtsx_exclusive_enter_ss (struct rtsx_chip*) ; 
 scalar_t__ rtsx_get_stat (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_is_ss_allowed (struct rtsx_chip*) ; 

__attribute__((used)) static void rtsx_manage_ss(struct rtsx_chip *chip)
{
	if (!rtsx_is_ss_allowed(chip) || chip->sd_io)
		return;

	if (rtsx_get_stat(chip) != RTSX_STAT_IDLE) {
		chip->ss_counter = 0;
		return;
	}

	if (chip->ss_counter < (chip->ss_idle_period / POLLING_INTERVAL))
		chip->ss_counter++;
	else
		rtsx_exclusive_enter_ss(chip);
}
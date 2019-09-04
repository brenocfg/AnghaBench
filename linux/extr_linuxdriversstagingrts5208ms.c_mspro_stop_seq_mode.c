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
struct ms_info {scalar_t__ total_sec_cnt; scalar_t__ seq_mode; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRO_STOP ; 
 int /*<<< orphan*/  RBCTL ; 
 int /*<<< orphan*/  RB_FLUSH ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WAIT_INT ; 
 int /*<<< orphan*/  ms_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ms_switch_clock (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mspro_stop_seq_mode(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval;

	if (ms_card->seq_mode) {
		retval = ms_switch_clock(chip);
		if (retval != STATUS_SUCCESS)
			return;

		ms_card->seq_mode = 0;
		ms_card->total_sec_cnt = 0;
		ms_send_cmd(chip, PRO_STOP, WAIT_INT);

		rtsx_write_register(chip, RBCTL, RB_FLUSH, RB_FLUSH);
	}
}
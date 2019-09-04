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
struct sd_info {scalar_t__ seq_mode; } ;
struct rtsx_chip {struct sd_info sd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBCTL ; 
 int /*<<< orphan*/  RB_FLUSH ; 
 int /*<<< orphan*/  SD_RSP_TYPE_R1b ; 
 int /*<<< orphan*/  SD_STS_ERR ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  STOP_TRANSMISSION ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_send_cmd_get_rsp (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int sd_switch_clock (struct rtsx_chip*) ; 
 int sd_wait_state_data_ready (struct rtsx_chip*,int,int,int) ; 

void sd_stop_seq_mode(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
	int retval;

	if (sd_card->seq_mode) {
		retval = sd_switch_clock(chip);
		if (retval != STATUS_SUCCESS)
			return;

		retval = sd_send_cmd_get_rsp(chip, STOP_TRANSMISSION, 0,
					     SD_RSP_TYPE_R1b, NULL, 0);
		if (retval != STATUS_SUCCESS)
			sd_set_err_code(chip, SD_STS_ERR);

		retval = sd_wait_state_data_ready(chip, 0x08, 1, 1000);
		if (retval != STATUS_SUCCESS)
			sd_set_err_code(chip, SD_STS_ERR);

		sd_card->seq_mode = 0;

		rtsx_write_register(chip, RBCTL, RB_FLUSH, RB_FLUSH);
	}
}
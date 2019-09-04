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
struct sd_info {scalar_t__ cleanup_counter; scalar_t__ seq_mode; } ;
struct ms_info {scalar_t__ cleanup_counter; scalar_t__ seq_mode; } ;
struct rtsx_chip {int card_ready; struct ms_info ms_card; struct sd_info sd_card; } ;
struct TYPE_2__ {scalar_t__ cleanup_counter; } ;

/* Variables and functions */
 scalar_t__ CHK_MSPRO (struct ms_info*) ; 
 int MS_CARD ; 
 scalar_t__ POLLING_WAIT_CNT ; 
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 int SD_CARD ; 
 int /*<<< orphan*/  ms_cleanup_work (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_cleanup_work (struct rtsx_chip*) ; 
 TYPE_1__* xd_card ; 
 int /*<<< orphan*/  xd_cleanup_work (struct rtsx_chip*) ; 

void do_remaining_work(struct rtsx_chip *chip)
{
	struct sd_info *sd_card = &chip->sd_card;
#ifdef XD_DELAY_WRITE
	struct xd_info *xd_card = &chip->xd_card;
#endif
	struct ms_info *ms_card = &chip->ms_card;

	if (chip->card_ready & SD_CARD) {
		if (sd_card->seq_mode) {
			rtsx_set_stat(chip, RTSX_STAT_RUN);
			sd_card->cleanup_counter++;
		} else {
			sd_card->cleanup_counter = 0;
		}
	}

#ifdef XD_DELAY_WRITE
	if (chip->card_ready & XD_CARD) {
		if (xd_card->delay_write.delay_write_flag) {
			rtsx_set_stat(chip, RTSX_STAT_RUN);
			xd_card->cleanup_counter++;
		} else {
			xd_card->cleanup_counter = 0;
		}
	}
#endif

	if (chip->card_ready & MS_CARD) {
		if (CHK_MSPRO(ms_card)) {
			if (ms_card->seq_mode) {
				rtsx_set_stat(chip, RTSX_STAT_RUN);
				ms_card->cleanup_counter++;
			} else {
				ms_card->cleanup_counter = 0;
			}
		} else {
#ifdef MS_DELAY_WRITE
			if (ms_card->delay_write.delay_write_flag) {
				rtsx_set_stat(chip, RTSX_STAT_RUN);
				ms_card->cleanup_counter++;
			} else {
				ms_card->cleanup_counter = 0;
			}
#endif
		}
	}

	if (sd_card->cleanup_counter > POLLING_WAIT_CNT)
		sd_cleanup_work(chip);

	if (xd_card->cleanup_counter > POLLING_WAIT_CNT)
		xd_cleanup_work(chip);

	if (ms_card->cleanup_counter > POLLING_WAIT_CNT)
		ms_cleanup_work(chip);
}
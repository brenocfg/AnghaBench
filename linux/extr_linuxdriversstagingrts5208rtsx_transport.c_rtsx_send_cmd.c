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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct rtsx_dev {scalar_t__ trans_result; int /*<<< orphan*/  trans_state; struct completion* done; int /*<<< orphan*/  reg_lock; scalar_t__ check_card_cd; } ;
struct rtsx_chip {int host_cmds_addr; int ci; int /*<<< orphan*/  int_reg; struct rtsx_dev* rtsx; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ MS_CARD ; 
 scalar_t__ MS_EXIST ; 
 int /*<<< orphan*/  RTSX_HCBAR ; 
 int /*<<< orphan*/  RTSX_HCBCTLR ; 
 scalar_t__ SD_CARD ; 
 scalar_t__ SD_EXIST ; 
 int /*<<< orphan*/  STATE_TRANS_CMD ; 
 int /*<<< orphan*/  STATE_TRANS_NONE ; 
 scalar_t__ TRANS_NOT_READY ; 
 scalar_t__ TRANS_RESULT_FAIL ; 
 scalar_t__ TRANS_RESULT_OK ; 
 scalar_t__ XD_CARD ; 
 scalar_t__ XD_EXIST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_stop_cmd (struct rtsx_chip*,scalar_t__) ; 
 int /*<<< orphan*/  rtsx_writel (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 long wait_for_completion_interruptible_timeout (struct completion*,int /*<<< orphan*/ ) ; 

int rtsx_send_cmd(struct rtsx_chip *chip, u8 card, int timeout)
{
	struct rtsx_dev *rtsx = chip->rtsx;
	struct completion trans_done;
	u32 val = BIT(31);
	long timeleft;
	int err = 0;

	if (card == SD_CARD)
		rtsx->check_card_cd = SD_EXIST;
	else if (card == MS_CARD)
		rtsx->check_card_cd = MS_EXIST;
	else if (card == XD_CARD)
		rtsx->check_card_cd = XD_EXIST;
	else
		rtsx->check_card_cd = 0;

	spin_lock_irq(&rtsx->reg_lock);

	/* set up data structures for the wakeup system */
	rtsx->done = &trans_done;
	rtsx->trans_result = TRANS_NOT_READY;
	init_completion(&trans_done);
	rtsx->trans_state = STATE_TRANS_CMD;

	rtsx_writel(chip, RTSX_HCBAR, chip->host_cmds_addr);

	val |= (u32)(chip->ci * 4) & 0x00FFFFFF;
	/* Hardware Auto Response */
	val |= 0x40000000;
	rtsx_writel(chip, RTSX_HCBCTLR, val);

	spin_unlock_irq(&rtsx->reg_lock);

	/* Wait for TRANS_OK_INT */
	timeleft = wait_for_completion_interruptible_timeout(
		&trans_done, msecs_to_jiffies(timeout));
	if (timeleft <= 0) {
		dev_dbg(rtsx_dev(chip), "chip->int_reg = 0x%x\n",
			chip->int_reg);
		err = -ETIMEDOUT;
		goto finish_send_cmd;
	}

	spin_lock_irq(&rtsx->reg_lock);
	if (rtsx->trans_result == TRANS_RESULT_FAIL)
		err = -EIO;
	else if (rtsx->trans_result == TRANS_RESULT_OK)
		err = 0;

	spin_unlock_irq(&rtsx->reg_lock);

finish_send_cmd:
	rtsx->done = NULL;
	rtsx->trans_state = STATE_TRANS_NONE;

	if (err < 0)
		rtsx_stop_cmd(chip, card);

	return err;
}
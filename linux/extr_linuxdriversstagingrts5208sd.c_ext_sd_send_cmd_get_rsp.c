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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int APP_CMD ; 
 scalar_t__ CARD_DATA_SOURCE ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int ETIMEDOUT ; 
 int PINGPONG_BUFFER ; 
 scalar_t__ PPBUF_BASE2 ; 
 int /*<<< orphan*/  READ_REG_CMD ; 
 scalar_t__ REG_SD_CFG2 ; 
 scalar_t__ REG_SD_CMD0 ; 
 scalar_t__ REG_SD_CMD1 ; 
 scalar_t__ REG_SD_CMD2 ; 
 scalar_t__ REG_SD_CMD3 ; 
 scalar_t__ REG_SD_CMD4 ; 
 scalar_t__ REG_SD_CMD5 ; 
 scalar_t__ REG_SD_STAT1 ; 
 scalar_t__ REG_SD_TRANSFER ; 
 int /*<<< orphan*/  SD_CARD ; 
 int SD_CRC7_ERR ; 
 int /*<<< orphan*/  SD_CRC_ERR ; 
 int SD_MAX_RETRY_COUNT ; 
 int SD_NO_CHECK_CRC7 ; 
 int SD_RSP_TYPE_R0 ; 
 int SD_RSP_TYPE_R1b ; 
 int SD_RSP_TYPE_R2 ; 
 int /*<<< orphan*/  SD_STS_ERR ; 
 int SD_TM_CMD_RSP ; 
 int /*<<< orphan*/  SD_TO_ERR ; 
 int SD_TRANSFER_END ; 
 int SD_TRANSFER_START ; 
 int SD_WAIT_BUSY_END ; 
 int SELECT_CARD ; 
 int SEND_STATUS ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int STOP_TRANSMISSION ; 
 int WRITE_MULTIPLE_BLOCK ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_sd_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int* rtsx_get_cmd_data (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int) ; 
 int sd_check_data0_status (struct rtsx_chip*) ; 
 int /*<<< orphan*/  sd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 

int ext_sd_send_cmd_get_rsp(struct rtsx_chip *chip, u8 cmd_idx, u32 arg,
			    u8 rsp_type, u8 *rsp, int rsp_len,
			    bool special_check)
{
	int retval;
	int timeout = 100;
	u16 reg_addr;
	u8 *ptr;
	int stat_idx = 0;
	int rty_cnt = 0;

	dev_dbg(rtsx_dev(chip), "EXT SD/MMC CMD %d\n", cmd_idx);

	if (rsp_type == SD_RSP_TYPE_R1b)
		timeout = 3000;

RTY_SEND_CMD:

	rtsx_init_cmd(chip);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD0, 0xFF, 0x40 | cmd_idx);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD1, 0xFF, (u8)(arg >> 24));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD2, 0xFF, (u8)(arg >> 16));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD3, 0xFF, (u8)(arg >> 8));
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CMD4, 0xFF, (u8)arg);

	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_CFG2, 0xFF, rsp_type);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE,
		     0x01, PINGPONG_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, REG_SD_TRANSFER,
		     0xFF, SD_TM_CMD_RSP | SD_TRANSFER_START);
	rtsx_add_cmd(chip, CHECK_REG_CMD, REG_SD_TRANSFER, SD_TRANSFER_END,
		     SD_TRANSFER_END);

	if (rsp_type == SD_RSP_TYPE_R2) {
		for (reg_addr = PPBUF_BASE2; reg_addr < PPBUF_BASE2 + 16;
		     reg_addr++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

		stat_idx = 17;
	} else if (rsp_type != SD_RSP_TYPE_R0) {
		for (reg_addr = REG_SD_CMD0; reg_addr <= REG_SD_CMD4;
		     reg_addr++)
			rtsx_add_cmd(chip, READ_REG_CMD, reg_addr, 0, 0);

		stat_idx = 6;
	}
	rtsx_add_cmd(chip, READ_REG_CMD, REG_SD_CMD5, 0, 0);

	rtsx_add_cmd(chip, READ_REG_CMD, REG_SD_STAT1, 0, 0);

	retval = rtsx_send_cmd(chip, SD_CARD, timeout);
	if (retval < 0) {
		if (retval == -ETIMEDOUT) {
			rtsx_clear_sd_error(chip);

			if (rsp_type & SD_WAIT_BUSY_END) {
				retval = sd_check_data0_status(chip);
				if (retval != STATUS_SUCCESS) {
					return retval;
				}
			} else {
				sd_set_err_code(chip, SD_TO_ERR);
			}
		}
		return STATUS_FAIL;
	}

	if (rsp_type == SD_RSP_TYPE_R0)
		return STATUS_SUCCESS;

	ptr = rtsx_get_cmd_data(chip) + 1;

	if ((ptr[0] & 0xC0) != 0) {
		sd_set_err_code(chip, SD_STS_ERR);
		return STATUS_FAIL;
	}

	if (!(rsp_type & SD_NO_CHECK_CRC7)) {
		if (ptr[stat_idx] & SD_CRC7_ERR) {
			if (cmd_idx == WRITE_MULTIPLE_BLOCK) {
				sd_set_err_code(chip, SD_CRC_ERR);
				return STATUS_FAIL;
			}
			if (rty_cnt < SD_MAX_RETRY_COUNT) {
				wait_timeout(20);
				rty_cnt++;
				goto RTY_SEND_CMD;
			} else {
				sd_set_err_code(chip, SD_CRC_ERR);
				return STATUS_FAIL;
			}
		}
	}

	if ((cmd_idx == SELECT_CARD) || (cmd_idx == APP_CMD) ||
	    (cmd_idx == SEND_STATUS) || (cmd_idx == STOP_TRANSMISSION)) {
		if ((cmd_idx != STOP_TRANSMISSION) && !special_check) {
			if (ptr[1] & 0x80) {
				return STATUS_FAIL;
			}
		}
#ifdef SUPPORT_SD_LOCK
		if (ptr[1] & 0x7D) {
#else
		if (ptr[1] & 0x7F) {
#endif
			return STATUS_FAIL;
		}
		if (ptr[2] & 0xF8) {
			return STATUS_FAIL;
		}

		if (cmd_idx == SELECT_CARD) {
			if (rsp_type == SD_RSP_TYPE_R2) {
				if ((ptr[3] & 0x1E) != 0x04) {
					return STATUS_FAIL;
				}
			}
		}
	}

	if (rsp && rsp_len)
		memcpy(rsp, ptr, rsp_len);

	return STATUS_SUCCESS;
}
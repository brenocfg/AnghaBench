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
typedef  int u16 ;
struct ms_info {int capacity; int /*<<< orphan*/  raw_sys_info; } ;
struct rtsx_chip {size_t card_wp; int* capacity; size_t* card2lun; struct ms_info ms_card; } ;

/* Variables and functions */
 scalar_t__ CHK_MS8BIT (struct ms_info*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MS_CARD ; 
 int MS_INT_BREQ ; 
 int MS_INT_CED ; 
 int MS_MAX_RETRY_COUNT ; 
 int /*<<< orphan*/  MS_TM_AUTO_READ ; 
 int /*<<< orphan*/  MS_TM_NORMAL_READ ; 
 int /*<<< orphan*/  MS_TRANS_CFG ; 
 int /*<<< orphan*/  NO_WAIT_INT ; 
 int PARALLEL_4BIT_IF ; 
 int PARALLEL_8BIT_IF ; 
 int /*<<< orphan*/  PRO_READ_ATRB ; 
 int /*<<< orphan*/  PRO_READ_LONG_DATA ; 
 int /*<<< orphan*/  PRO_WRITE_REG ; 
 int /*<<< orphan*/  Pro_IntReg ; 
 int /*<<< orphan*/  Pro_SystemParm ; 
 int STATUS_ERROR ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WAIT_INT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int ms_send_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ms_set_rw_reg_addr (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int ms_transfer_data (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int ms_transfer_tpc (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ms_write_bytes (struct rtsx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  rtsx_clear_ms_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ms_read_attribute_info(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int retval, i;
	u8 val, *buf, class_code, device_type, sub_class, data[16];
	u16 total_blk = 0, blk_size = 0;
#ifdef SUPPORT_MSXC
	u32 xc_total_blk = 0, xc_blk_size = 0;
#endif
	u32 sys_info_addr = 0, sys_info_size;
#ifdef SUPPORT_PCGL_1P18
	u32 model_name_addr = 0, model_name_size;
	int found_sys_info = 0, found_model_name = 0;
#endif

	retval = ms_set_rw_reg_addr(chip, Pro_IntReg, 2, Pro_SystemParm, 7);
	if (retval != STATUS_SUCCESS) {
		return STATUS_FAIL;
	}

	if (CHK_MS8BIT(ms_card))
		data[0] = PARALLEL_8BIT_IF;
	else
		data[0] = PARALLEL_4BIT_IF;

	data[1] = 0;

	data[2] = 0x40;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;

	for (i = 0; i < MS_MAX_RETRY_COUNT; i++) {
		retval = ms_write_bytes(chip, PRO_WRITE_REG, 7, NO_WAIT_INT,
					data, 8);
		if (retval == STATUS_SUCCESS)
			break;
	}
	if (retval != STATUS_SUCCESS) {
		return STATUS_FAIL;
	}

	buf = kmalloc(64 * 512, GFP_KERNEL);
	if (!buf) {
		return STATUS_ERROR;
	}

	for (i = 0; i < MS_MAX_RETRY_COUNT; i++) {
		retval = ms_send_cmd(chip, PRO_READ_ATRB, WAIT_INT);
		if (retval != STATUS_SUCCESS)
			continue;

		retval = rtsx_read_register(chip, MS_TRANS_CFG, &val);
		if (retval != STATUS_SUCCESS) {
			kfree(buf);
			return STATUS_FAIL;
		}
		if (!(val & MS_INT_BREQ)) {
			kfree(buf);
			return STATUS_FAIL;
		}
		retval = ms_transfer_data(chip, MS_TM_AUTO_READ,
					  PRO_READ_LONG_DATA, 0x40, WAIT_INT,
					  0, 0, buf, 64 * 512);
		if (retval == STATUS_SUCCESS)
			break;

		rtsx_clear_ms_error(chip);
	}
	if (retval != STATUS_SUCCESS) {
		kfree(buf);
		return STATUS_FAIL;
	}

	i = 0;
	do {
		retval = rtsx_read_register(chip, MS_TRANS_CFG, &val);
		if (retval != STATUS_SUCCESS) {
			kfree(buf);
			return STATUS_FAIL;
		}

		if ((val & MS_INT_CED) || !(val & MS_INT_BREQ))
			break;

		retval = ms_transfer_tpc(chip, MS_TM_NORMAL_READ,
					 PRO_READ_LONG_DATA, 0, WAIT_INT);
		if (retval != STATUS_SUCCESS) {
			kfree(buf);
			return STATUS_FAIL;
		}

		i++;
	} while (i < 1024);

	if ((buf[0] != 0xa5) && (buf[1] != 0xc3)) {
		/* Signature code is wrong */
		kfree(buf);
		return STATUS_FAIL;
	}

	if ((buf[4] < 1) || (buf[4] > 12)) {
		kfree(buf);
		return STATUS_FAIL;
	}

	for (i = 0; i < buf[4]; i++) {
		int cur_addr_off = 16 + i * 12;

#ifdef SUPPORT_MSXC
		if ((buf[cur_addr_off + 8] == 0x10) ||
		    (buf[cur_addr_off + 8] == 0x13)) {
#else
		if (buf[cur_addr_off + 8] == 0x10) {
#endif
			sys_info_addr = ((u32)buf[cur_addr_off + 0] << 24) |
				((u32)buf[cur_addr_off + 1] << 16) |
				((u32)buf[cur_addr_off + 2] << 8) |
				buf[cur_addr_off + 3];
			sys_info_size = ((u32)buf[cur_addr_off + 4] << 24) |
				((u32)buf[cur_addr_off + 5] << 16) |
				((u32)buf[cur_addr_off + 6] << 8) |
				buf[cur_addr_off + 7];
			dev_dbg(rtsx_dev(chip), "sys_info_addr = 0x%x, sys_info_size = 0x%x\n",
				sys_info_addr, sys_info_size);
			if (sys_info_size != 96)  {
				kfree(buf);
				return STATUS_FAIL;
			}
			if (sys_info_addr < 0x1A0) {
				kfree(buf);
				return STATUS_FAIL;
			}
			if ((sys_info_size + sys_info_addr) > 0x8000) {
				kfree(buf);
				return STATUS_FAIL;
			}

#ifdef SUPPORT_MSXC
			if (buf[cur_addr_off + 8] == 0x13)
				ms_card->ms_type |= MS_XC;
#endif
#ifdef SUPPORT_PCGL_1P18
			found_sys_info = 1;
#else
			break;
#endif
		}
#ifdef SUPPORT_PCGL_1P18
		if (buf[cur_addr_off + 8] == 0x15) {
			model_name_addr = ((u32)buf[cur_addr_off + 0] << 24) |
				((u32)buf[cur_addr_off + 1] << 16) |
				((u32)buf[cur_addr_off + 2] << 8) |
				buf[cur_addr_off + 3];
			model_name_size = ((u32)buf[cur_addr_off + 4] << 24) |
				((u32)buf[cur_addr_off + 5] << 16) |
				((u32)buf[cur_addr_off + 6] << 8) |
				buf[cur_addr_off + 7];
			dev_dbg(rtsx_dev(chip), "model_name_addr = 0x%x, model_name_size = 0x%x\n",
				model_name_addr, model_name_size);
			if (model_name_size != 48)  {
				kfree(buf);
				return STATUS_FAIL;
			}
			if (model_name_addr < 0x1A0) {
				kfree(buf);
				return STATUS_FAIL;
			}
			if ((model_name_size + model_name_addr) > 0x8000) {
				kfree(buf);
				return STATUS_FAIL;
			}

			found_model_name = 1;
		}

		if (found_sys_info && found_model_name)
			break;
#endif
	}

	if (i == buf[4]) {
		kfree(buf);
		return STATUS_FAIL;
	}

	class_code =  buf[sys_info_addr + 0];
	device_type = buf[sys_info_addr + 56];
	sub_class = buf[sys_info_addr + 46];
#ifdef SUPPORT_MSXC
	if (CHK_MSXC(ms_card)) {
		xc_total_blk = ((u32)buf[sys_info_addr + 6] << 24) |
				((u32)buf[sys_info_addr + 7] << 16) |
				((u32)buf[sys_info_addr + 8] << 8) |
				buf[sys_info_addr + 9];
		xc_blk_size = ((u32)buf[sys_info_addr + 32] << 24) |
				((u32)buf[sys_info_addr + 33] << 16) |
				((u32)buf[sys_info_addr + 34] << 8) |
				buf[sys_info_addr + 35];
		dev_dbg(rtsx_dev(chip), "xc_total_blk = 0x%x, xc_blk_size = 0x%x\n",
			xc_total_blk, xc_blk_size);
	} else {
		total_blk = ((u16)buf[sys_info_addr + 6] << 8) |
			buf[sys_info_addr + 7];
		blk_size = ((u16)buf[sys_info_addr + 2] << 8) |
			buf[sys_info_addr + 3];
		dev_dbg(rtsx_dev(chip), "total_blk = 0x%x, blk_size = 0x%x\n",
			total_blk, blk_size);
	}
#else
	total_blk = ((u16)buf[sys_info_addr + 6] << 8) | buf[sys_info_addr + 7];
	blk_size = ((u16)buf[sys_info_addr + 2] << 8) | buf[sys_info_addr + 3];
	dev_dbg(rtsx_dev(chip), "total_blk = 0x%x, blk_size = 0x%x\n",
		total_blk, blk_size);
#endif

	dev_dbg(rtsx_dev(chip), "class_code = 0x%x, device_type = 0x%x, sub_class = 0x%x\n",
		class_code, device_type, sub_class);

	memcpy(ms_card->raw_sys_info, buf + sys_info_addr, 96);
#ifdef SUPPORT_PCGL_1P18
	memcpy(ms_card->raw_model_name, buf + model_name_addr, 48);
#endif

	kfree(buf);

#ifdef SUPPORT_MSXC
	if (CHK_MSXC(ms_card)) {
		if (class_code != 0x03) {
			return STATUS_FAIL;
		}
	} else {
		if (class_code != 0x02) {
			return STATUS_FAIL;
		}
	}
#else
	if (class_code != 0x02) {
		return STATUS_FAIL;
	}
#endif

	if (device_type != 0x00) {
		if ((device_type == 0x01) || (device_type == 0x02) ||
		    (device_type == 0x03)) {
			chip->card_wp |= MS_CARD;
		} else {
			return STATUS_FAIL;
		}
	}

	if (sub_class & 0xC0) {
		return STATUS_FAIL;
	}

	dev_dbg(rtsx_dev(chip), "class_code: 0x%x, device_type: 0x%x, sub_class: 0x%x\n",
		class_code, device_type, sub_class);

#ifdef SUPPORT_MSXC
	if (CHK_MSXC(ms_card)) {
		chip->capacity[chip->card2lun[MS_CARD]] =
			ms_card->capacity = xc_total_blk * xc_blk_size;
	} else {
		chip->capacity[chip->card2lun[MS_CARD]] =
			ms_card->capacity = total_blk * blk_size;
	}
#else
	ms_card->capacity = total_blk * blk_size;
	chip->capacity[chip->card2lun[MS_CARD]] = ms_card->capacity;
#endif

	return STATUS_SUCCESS;
}
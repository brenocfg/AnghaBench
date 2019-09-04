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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ max_data_size; scalar_t__ max_cmd_size; scalar_t__* cmd_buf; scalar_t__ done_sent; } ;
struct ath6kl {TYPE_1__ bmi; } ;
typedef  int /*<<< orphan*/  rx_len ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  cid ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BMI ; 
 scalar_t__ BMI_READ_MEMORY ; 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int) ; 
 int ath6kl_hif_bmi_read (struct ath6kl*,scalar_t__*,scalar_t__) ; 
 int ath6kl_hif_bmi_write (struct ath6kl*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

int ath6kl_bmi_read(struct ath6kl *ar, u32 addr, u8 *buf, u32 len)
{
	u32 cid = BMI_READ_MEMORY;
	int ret;
	u32 offset;
	u32 len_remain, rx_len;
	u16 size;

	if (ar->bmi.done_sent) {
		ath6kl_err("bmi done sent already, cmd %d disallowed\n", cid);
		return -EACCES;
	}

	size = ar->bmi.max_data_size + sizeof(cid) + sizeof(addr) + sizeof(len);
	if (size > ar->bmi.max_cmd_size) {
		WARN_ON(1);
		return -EINVAL;
	}
	memset(ar->bmi.cmd_buf, 0, size);

	ath6kl_dbg(ATH6KL_DBG_BMI,
		   "bmi read memory: device: addr: 0x%x, len: %d\n",
		   addr, len);

	len_remain = len;

	while (len_remain) {
		rx_len = (len_remain < ar->bmi.max_data_size) ?
					len_remain : ar->bmi.max_data_size;
		offset = 0;
		memcpy(&(ar->bmi.cmd_buf[offset]), &cid, sizeof(cid));
		offset += sizeof(cid);
		memcpy(&(ar->bmi.cmd_buf[offset]), &addr, sizeof(addr));
		offset += sizeof(addr);
		memcpy(&(ar->bmi.cmd_buf[offset]), &rx_len, sizeof(rx_len));
		offset += sizeof(len);

		ret = ath6kl_hif_bmi_write(ar, ar->bmi.cmd_buf, offset);
		if (ret) {
			ath6kl_err("Unable to write to the device: %d\n",
				   ret);
			return ret;
		}
		ret = ath6kl_hif_bmi_read(ar, ar->bmi.cmd_buf, rx_len);
		if (ret) {
			ath6kl_err("Unable to read from the device: %d\n",
				   ret);
			return ret;
		}
		memcpy(&buf[len - len_remain], ar->bmi.cmd_buf, rx_len);
		len_remain -= rx_len; addr += rx_len;
	}

	return 0;
}
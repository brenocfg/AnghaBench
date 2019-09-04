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
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 
 int HALMAC_RET_DL_RSVD_PAGE_FAIL ; 
 int HALMAC_RET_POLLING_BCN_VALID_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int HALMAC_RET_ZERO_LEN_RSVD_PACKET ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PLATFORM_SEND_RSVD_PAGE (void*,int*,int) ; 
 scalar_t__ REG_BCN_CTRL ; 
 scalar_t__ REG_CR ; 
 scalar_t__ REG_FIFOPAGE_CTRL_2 ; 
 scalar_t__ REG_FWHW_TXQ_CTRL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

enum halmac_ret_status
halmac_download_rsvd_page_88xx(struct halmac_adapter *halmac_adapter,
			       u8 *hal_buf, u32 size)
{
	u8 restore[3];
	u8 value8;
	u32 counter;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;
	enum halmac_ret_status status = HALMAC_RET_SUCCESS;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	if (size == 0) {
		HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
				"Rsvd page packet size is zero!!\n");
		return HALMAC_RET_ZERO_LEN_RSVD_PACKET;
	}

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_FIFOPAGE_CTRL_2 + 1);
	value8 = (u8)(value8 | BIT(7));
	HALMAC_REG_WRITE_8(halmac_adapter, REG_FIFOPAGE_CTRL_2 + 1, value8);

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_CR + 1);
	restore[0] = value8;
	value8 = (u8)(value8 | BIT(0));
	HALMAC_REG_WRITE_8(halmac_adapter, REG_CR + 1, value8);

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_BCN_CTRL);
	restore[1] = value8;
	value8 = (u8)((value8 & ~(BIT(3))) | BIT(4));
	HALMAC_REG_WRITE_8(halmac_adapter, REG_BCN_CTRL, value8);

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_FWHW_TXQ_CTRL + 2);
	restore[2] = value8;
	value8 = (u8)(value8 & ~(BIT(6)));
	HALMAC_REG_WRITE_8(halmac_adapter, REG_FWHW_TXQ_CTRL + 2, value8);

	if (!PLATFORM_SEND_RSVD_PAGE(driver_adapter, hal_buf, size)) {
		pr_err("PLATFORM_SEND_RSVD_PAGE 1 error!!\n");
		status = HALMAC_RET_DL_RSVD_PAGE_FAIL;
	}

	/* Check Bcn_Valid_Bit */
	counter = 1000;
	while (!(HALMAC_REG_READ_8(halmac_adapter, REG_FIFOPAGE_CTRL_2 + 1) &
		 BIT(7))) {
		udelay(10);
		counter--;
		if (counter == 0) {
			pr_err("Polling Bcn_Valid_Fail error!!\n");
			status = HALMAC_RET_POLLING_BCN_VALID_FAIL;
			break;
		}
	}

	value8 = HALMAC_REG_READ_8(halmac_adapter, REG_FIFOPAGE_CTRL_2 + 1);
	HALMAC_REG_WRITE_8(halmac_adapter, REG_FIFOPAGE_CTRL_2 + 1,
			   (value8 | BIT(7)));

	HALMAC_REG_WRITE_8(halmac_adapter, REG_FWHW_TXQ_CTRL + 2, restore[2]);
	HALMAC_REG_WRITE_8(halmac_adapter, REG_BCN_CTRL, restore[1]);
	HALMAC_REG_WRITE_8(halmac_adapter, REG_CR + 1, restore[0]);

	return status;
}
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
struct halmac_adapter {scalar_t__ halmac_interface; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ HALMAC_INTERFACE_SDIO ; 
 int /*<<< orphan*/  HALMAC_MSG_INIT ; 
 int HALMAC_RET_PLATFORM_API_INCORRECT ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int PLATFORM_REG_READ_32 (void*,int) ; 
 int /*<<< orphan*/  PLATFORM_REG_WRITE_32 (void*,int,int) ; 
 int PLATFORM_SDIO_CMD52_READ (void*,int) ; 
 int /*<<< orphan*/  PLATFORM_SDIO_CMD52_WRITE (void*,int,int) ; 
 int PLATFORM_SDIO_CMD53_READ_32 (void*,int) ; 
 int /*<<< orphan*/  PLATFORM_SDIO_CMD53_WRITE_32 (void*,int,int) ; 
 int REG_PAGE5_DUMMY ; 
 int WLAN_IOREG_OFFSET ; 
 int halmac_convert_to_sdio_bus_offset_88xx (struct halmac_adapter*,int*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

enum halmac_ret_status
halmac_verify_io_88xx(struct halmac_adapter *halmac_adapter)
{
	u8 value8, wvalue8;
	u32 value32, value32_2, wvalue32;
	u32 halmac_offset;
	void *driver_adapter = NULL;
	enum halmac_ret_status ret_status = HALMAC_RET_SUCCESS;

	driver_adapter = halmac_adapter->driver_adapter;

	if (halmac_adapter->halmac_interface == HALMAC_INTERFACE_SDIO) {
		halmac_offset = REG_PAGE5_DUMMY;
		if ((halmac_offset & 0xFFFF0000) == 0)
			halmac_offset |= WLAN_IOREG_OFFSET;

		ret_status = halmac_convert_to_sdio_bus_offset_88xx(
			halmac_adapter, &halmac_offset);

		/* Verify CMD52 R/W */
		wvalue8 = 0xab;
		PLATFORM_SDIO_CMD52_WRITE(driver_adapter, halmac_offset,
					  wvalue8);

		value8 =
			PLATFORM_SDIO_CMD52_READ(driver_adapter, halmac_offset);

		if (value8 != wvalue8) {
			pr_err("cmd52 r/w fail write = %X read = %X\n", wvalue8,
			       value8);
			ret_status = HALMAC_RET_PLATFORM_API_INCORRECT;
		} else {
			HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT,
					DBG_DMESG, "cmd52 r/w ok\n");
		}

		/* Verify CMD53 R/W */
		PLATFORM_SDIO_CMD52_WRITE(driver_adapter, halmac_offset, 0xaa);
		PLATFORM_SDIO_CMD52_WRITE(driver_adapter, halmac_offset + 1,
					  0xbb);
		PLATFORM_SDIO_CMD52_WRITE(driver_adapter, halmac_offset + 2,
					  0xcc);
		PLATFORM_SDIO_CMD52_WRITE(driver_adapter, halmac_offset + 3,
					  0xdd);

		value32 = PLATFORM_SDIO_CMD53_READ_32(driver_adapter,
						      halmac_offset);

		if (value32 != 0xddccbbaa) {
			pr_err("cmd53 r fail : read = %X\n", value32);
			ret_status = HALMAC_RET_PLATFORM_API_INCORRECT;
		} else {
			HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT,
					DBG_DMESG, "cmd53 r ok\n");
		}

		wvalue32 = 0x11223344;
		PLATFORM_SDIO_CMD53_WRITE_32(driver_adapter, halmac_offset,
					     wvalue32);

		value32 = PLATFORM_SDIO_CMD53_READ_32(driver_adapter,
						      halmac_offset);

		if (value32 != wvalue32) {
			pr_err("cmd53 w fail\n");
			ret_status = HALMAC_RET_PLATFORM_API_INCORRECT;
		} else {
			HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT,
					DBG_DMESG, "cmd53 w ok\n");
		}

		value32 = PLATFORM_SDIO_CMD53_READ_32(
			driver_adapter,
			halmac_offset + 2); /* value32 should be 0x33441122 */

		wvalue32 = 0x11225566;
		PLATFORM_SDIO_CMD53_WRITE_32(driver_adapter, halmac_offset,
					     wvalue32);

		value32_2 = PLATFORM_SDIO_CMD53_READ_32(
			driver_adapter,
			halmac_offset + 2); /* value32 should be 0x55661122 */
		if (value32_2 == value32) {
			pr_err("cmd52 is used for HAL_SDIO_CMD53_READ_32\n");
			ret_status = HALMAC_RET_PLATFORM_API_INCORRECT;
		} else {
			HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT,
					DBG_DMESG, "cmd53 is correctly used\n");
		}
	} else {
		wvalue32 = 0x77665511;
		PLATFORM_REG_WRITE_32(driver_adapter, REG_PAGE5_DUMMY,
				      wvalue32);

		value32 = PLATFORM_REG_READ_32(driver_adapter, REG_PAGE5_DUMMY);
		if (value32 != wvalue32) {
			pr_err("reg rw\n");
			ret_status = HALMAC_RET_PLATFORM_API_INCORRECT;
		} else {
			HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_INIT,
					DBG_DMESG, "reg rw ok\n");
		}
	}

	return ret_status;
}
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
typedef  scalar_t__ u32 ;
struct halmac_adapter {void* driver_adapter; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 scalar_t__ HALMAC_RET_ADAPTER_INVALID ; 
 scalar_t__ HALMAC_RET_API_INVALID ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int HALMAC_SDIO_CMD_ADDR_SDIO_REG ; 
 int HALMAC_SDIO_LOCAL_MSK ; 
 scalar_t__ PLATFORM_SDIO_CMD52_READ (void*,int) ; 
 scalar_t__ PLATFORM_SDIO_CMD53_READ_32 (void*,int) ; 
 int /*<<< orphan*/  PLATFORM_SDIO_CMD53_WRITE_32 (void*,int,scalar_t__) ; 
 int REG_SDIO_INDIRECT_REG_CFG ; 
 int REG_SDIO_INDIRECT_REG_DATA ; 
 scalar_t__ halmac_adapter_validate (struct halmac_adapter*) ; 
 scalar_t__ halmac_api_validate (struct halmac_adapter*) ; 

u32 halmac_reg_read_indirect_32_sdio_88xx(struct halmac_adapter *halmac_adapter,
					  u32 halmac_offset)
{
	u8 rtemp;
	u32 counter = 1000;
	void *driver_adapter = NULL;

	union {
		u32 dword;
		u8 byte[4];
	} value32 = {0x00000000};

	if (halmac_adapter_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_ADAPTER_INVALID;

	if (halmac_api_validate(halmac_adapter) != HALMAC_RET_SUCCESS)
		return HALMAC_RET_API_INVALID;

	driver_adapter = halmac_adapter->driver_adapter;

	PLATFORM_SDIO_CMD53_WRITE_32(
		driver_adapter,
		(HALMAC_SDIO_CMD_ADDR_SDIO_REG << 13) |
			(REG_SDIO_INDIRECT_REG_CFG & HALMAC_SDIO_LOCAL_MSK),
		halmac_offset | BIT(19) | BIT(17));

	do {
		rtemp = PLATFORM_SDIO_CMD52_READ(
			driver_adapter,
			(HALMAC_SDIO_CMD_ADDR_SDIO_REG << 13) |
				((REG_SDIO_INDIRECT_REG_CFG + 2) &
				 HALMAC_SDIO_LOCAL_MSK));
		counter--;
	} while ((rtemp & BIT(4)) != 0 && counter > 0);

	value32.dword = PLATFORM_SDIO_CMD53_READ_32(
		driver_adapter,
		(HALMAC_SDIO_CMD_ADDR_SDIO_REG << 13) |
			(REG_SDIO_INDIRECT_REG_DATA & HALMAC_SDIO_LOCAL_MSK));

	return value32.dword;
}
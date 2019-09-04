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
typedef  int u16 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_MSG_DBI ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_16 (struct halmac_adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ REG_DBI_FLAG_V1 ; 
 int /*<<< orphan*/  REG_DBI_RDATA_V1 ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

u32 halmac_dbi_read32_88xx(struct halmac_adapter *halmac_adapter, u16 addr)
{
	u16 read_addr = addr & 0x0ffc;
	u8 tmp_u1b = 0;
	u32 count = 0;
	u32 ret = 0;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_REG_WRITE_16(halmac_adapter, REG_DBI_FLAG_V1, read_addr);

	HALMAC_REG_WRITE_8(halmac_adapter, REG_DBI_FLAG_V1 + 2, 0x2);
	tmp_u1b = HALMAC_REG_READ_8(halmac_adapter, REG_DBI_FLAG_V1 + 2);

	count = 20;
	while (tmp_u1b && count != 0) {
		udelay(10);
		tmp_u1b =
			HALMAC_REG_READ_8(halmac_adapter, REG_DBI_FLAG_V1 + 2);
		count--;
	}

	if (tmp_u1b) {
		ret = 0xFFFF;
		pr_err("DBI read fail!\n");
	} else {
		ret = HALMAC_REG_READ_32(halmac_adapter, REG_DBI_RDATA_V1);
		HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_DBI, DBG_DMESG,
				"Read Value = %x\n", ret);
	}

	return ret;
}
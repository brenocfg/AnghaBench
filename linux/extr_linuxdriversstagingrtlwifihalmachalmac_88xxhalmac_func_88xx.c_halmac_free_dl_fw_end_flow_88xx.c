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
typedef  int u32 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 scalar_t__ HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,scalar_t__) ; 
 int HALMAC_RET_DLFW_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 scalar_t__ ID_INFORM_DLEMEM_RDY ; 
 scalar_t__ REG_C2HEVT_3 ; 
 scalar_t__ REG_HMETFR ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

enum halmac_ret_status
halmac_free_dl_fw_end_flow_88xx(struct halmac_adapter *halmac_adapter)
{
	u32 counter;
	struct halmac_api *halmac_api =
		(struct halmac_api *)halmac_adapter->halmac_api;

	counter = 100;
	while (HALMAC_REG_READ_8(halmac_adapter, REG_HMETFR + 3) != 0) {
		counter--;
		if (counter == 0) {
			pr_err("[ERR]0x1CF != 0\n");
			return HALMAC_RET_DLFW_FAIL;
		}
		usleep_range(50, 60);
	}

	HALMAC_REG_WRITE_8(halmac_adapter, REG_HMETFR + 3,
			   ID_INFORM_DLEMEM_RDY);

	counter = 10000;
	while (HALMAC_REG_READ_8(halmac_adapter, REG_C2HEVT_3 + 3) !=
	       ID_INFORM_DLEMEM_RDY) {
		counter--;
		if (counter == 0) {
			pr_err("[ERR]0x1AF != 0x80\n");
			return HALMAC_RET_DLFW_FAIL;
		}
		usleep_range(50, 60);
	}

	HALMAC_REG_WRITE_8(halmac_adapter, REG_C2HEVT_3 + 3, 0);

	return HALMAC_RET_SUCCESS;
}
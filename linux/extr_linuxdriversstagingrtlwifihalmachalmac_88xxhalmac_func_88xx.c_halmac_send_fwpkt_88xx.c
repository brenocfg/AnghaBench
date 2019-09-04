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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_DL_RSVD_PAGE_FAIL ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 scalar_t__ halmac_download_rsvd_page_88xx (struct halmac_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_send_fwpkt_88xx(struct halmac_adapter *halmac_adapter, u8 *ram_code,
		       u32 code_size)
{
	if (halmac_download_rsvd_page_88xx(halmac_adapter, ram_code,
					   code_size) != HALMAC_RET_SUCCESS) {
		pr_err("PLATFORM_SEND_RSVD_PAGE 0 error!!\n");
		return HALMAC_RET_DL_RSVD_PAGE_FAIL;
	}

	return HALMAC_RET_SUCCESS;
}
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
struct TYPE_2__ {scalar_t__ txdesc_size; } ;
struct halmac_adapter {TYPE_1__ hw_config_info; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HALMAC_RET_MALLOC_FAIL ; 
 int HALMAC_RET_PLATFORM_API_INCORRECT ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HAL_FIFO_SEL_RSVD_PAGE ; 
 int halmac_download_rsvd_page_88xx (struct halmac_adapter*,scalar_t__*,scalar_t__) ; 
 int halmac_dump_fifo_88xx (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_verify_send_rsvd_page_88xx(struct halmac_adapter *halmac_adapter)
{
	u8 *rsvd_buf = NULL;
	u8 *rsvd_page = NULL;
	u32 i;
	u32 h2c_pkt_verify_size = 64, h2c_pkt_verify_payload = 0xab;
	void *driver_adapter = NULL;
	enum halmac_ret_status ret_status = HALMAC_RET_SUCCESS;

	driver_adapter = halmac_adapter->driver_adapter;

	rsvd_buf = kzalloc(h2c_pkt_verify_size, GFP_KERNEL);

	if (!rsvd_buf)
		return HALMAC_RET_MALLOC_FAIL;

	memset(rsvd_buf, (u8)h2c_pkt_verify_payload, h2c_pkt_verify_size);

	ret_status = halmac_download_rsvd_page_88xx(halmac_adapter, rsvd_buf,
						    h2c_pkt_verify_size);

	if (ret_status != HALMAC_RET_SUCCESS) {
		kfree(rsvd_buf);
		return ret_status;
	}

	rsvd_page = kzalloc(h2c_pkt_verify_size +
				    halmac_adapter->hw_config_info.txdesc_size,
			    GFP_KERNEL);

	if (!rsvd_page) {
		kfree(rsvd_buf);
		return HALMAC_RET_MALLOC_FAIL;
	}

	ret_status = halmac_dump_fifo_88xx(
		halmac_adapter, HAL_FIFO_SEL_RSVD_PAGE, 0,
		h2c_pkt_verify_size +
			halmac_adapter->hw_config_info.txdesc_size,
		rsvd_page);

	if (ret_status != HALMAC_RET_SUCCESS) {
		kfree(rsvd_buf);
		kfree(rsvd_page);
		return ret_status;
	}

	for (i = 0; i < h2c_pkt_verify_size; i++) {
		if (*(rsvd_buf + i) !=
		    *(rsvd_page +
		      (i + halmac_adapter->hw_config_info.txdesc_size))) {
			pr_err("[ERR]Compare RSVD page Fail\n");
			ret_status = HALMAC_RET_PLATFORM_API_INCORRECT;
		}
	}

	kfree(rsvd_buf);
	kfree(rsvd_page);

	return ret_status;
}
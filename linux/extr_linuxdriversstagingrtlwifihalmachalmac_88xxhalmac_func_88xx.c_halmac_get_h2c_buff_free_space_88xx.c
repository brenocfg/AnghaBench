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
typedef  void* u32 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {void* h2c_buff_size; void* h2c_buf_free_space; scalar_t__ halmac_api; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT_MASK_H2C_READ_ADDR ; 
 int BIT_MASK_H2C_WR_ADDR ; 
 int HALMAC_REG_READ_32 (struct halmac_adapter*,int /*<<< orphan*/ ) ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  REG_H2C_PKT_READADDR ; 
 int /*<<< orphan*/  REG_H2C_PKT_WRITEADDR ; 

enum halmac_ret_status
halmac_get_h2c_buff_free_space_88xx(struct halmac_adapter *halmac_adapter)
{
	u32 hw_wptr, fw_rptr;
	struct halmac_api *halmac_api =
		(struct halmac_api *)halmac_adapter->halmac_api;

	hw_wptr = HALMAC_REG_READ_32(halmac_adapter, REG_H2C_PKT_WRITEADDR) &
		  BIT_MASK_H2C_WR_ADDR;
	fw_rptr = HALMAC_REG_READ_32(halmac_adapter, REG_H2C_PKT_READADDR) &
		  BIT_MASK_H2C_READ_ADDR;

	if (hw_wptr >= fw_rptr)
		halmac_adapter->h2c_buf_free_space =
			halmac_adapter->h2c_buff_size - (hw_wptr - fw_rptr);
	else
		halmac_adapter->h2c_buf_free_space = fw_rptr - hw_wptr;

	return HALMAC_RET_SUCCESS;
}
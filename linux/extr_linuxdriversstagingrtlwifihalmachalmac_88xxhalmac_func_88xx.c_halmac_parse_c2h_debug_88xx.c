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
typedef  int /*<<< orphan*/  u32 ;
struct halmac_adapter {void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 scalar_t__ C2H_DBG_CONTENT_MAX_LENGTH ; 
 int C2H_DBG_HEADER_LENGTH ; 
 scalar_t__ C2H_HDR_GET_LEN (scalar_t__*) ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_MSG_H2C ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,char*) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_parse_c2h_debug_88xx(struct halmac_adapter *halmac_adapter, u8 *c2h_buf,
			    u32 c2h_size)
{
	void *driver_adapter = NULL;
	u8 *c2h_buf_local = (u8 *)NULL;
	u32 c2h_size_local = 0;
	u8 dbg_content_length = 0;
	u8 dbg_seq_num = 0;

	driver_adapter = halmac_adapter->driver_adapter;
	c2h_buf_local = c2h_buf;
	c2h_size_local = c2h_size;

	dbg_content_length = (u8)C2H_HDR_GET_LEN((u8 *)c2h_buf_local);

	if (dbg_content_length > C2H_DBG_CONTENT_MAX_LENGTH)
		return HALMAC_RET_SUCCESS;

	*(c2h_buf_local + C2H_DBG_HEADER_LENGTH + dbg_content_length - 2) =
		'\n';
	dbg_seq_num = (u8)(*(c2h_buf_local + C2H_DBG_HEADER_LENGTH));
	HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_H2C, DBG_DMESG,
			"[RTKFW, SEQ=%d]: %s", dbg_seq_num,
			(char *)(c2h_buf_local + C2H_DBG_HEADER_LENGTH + 1));

	return HALMAC_RET_SUCCESS;
}
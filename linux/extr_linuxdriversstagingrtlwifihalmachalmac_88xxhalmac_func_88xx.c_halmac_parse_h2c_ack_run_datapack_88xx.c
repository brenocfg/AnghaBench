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
struct halmac_adapter {void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_cmd_process_status { ____Placeholder_halmac_cmd_process_status } halmac_cmd_process_status ;

/* Variables and functions */
 int HALMAC_CMD_PROCESS_UNDEFINE ; 
 int /*<<< orphan*/  HALMAC_FEATURE_RUN_DATAPACK ; 
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  PLATFORM_EVENT_INDICATION (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum halmac_ret_status
halmac_parse_h2c_ack_run_datapack_88xx(struct halmac_adapter *halmac_adapter,
				       u8 *c2h_buf, u32 c2h_size)
{
	void *driver_adapter = halmac_adapter->driver_adapter;
	enum halmac_cmd_process_status process_status =
		HALMAC_CMD_PROCESS_UNDEFINE;

	PLATFORM_EVENT_INDICATION(driver_adapter, HALMAC_FEATURE_RUN_DATAPACK,
				  process_status, NULL, 0);

	return HALMAC_RET_SUCCESS;
}
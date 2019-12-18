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
typedef  int /*<<< orphan*/  u32 ;
struct sst_ipc_message {int size; struct sst_hsw_ipc_device_config_req* data; int /*<<< orphan*/  header; } ;
struct sst_hsw_ipc_device_config_req {int ssp_interface; int clock_frequency; int mode; int channels; int /*<<< orphan*/  clock_divider; } ;
struct sst_hsw {int dx_dev; int dx_mclk; int dx_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; int /*<<< orphan*/  dx_clock_divider; } ;
typedef  enum sst_hsw_device_mode { ____Placeholder_sst_hsw_device_mode } sst_hsw_device_mode ;
typedef  enum sst_hsw_device_mclk { ____Placeholder_sst_hsw_device_mclk } sst_hsw_device_mclk ;
typedef  enum sst_hsw_device_id { ____Placeholder_sst_hsw_device_id } sst_hsw_device_id ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_GLB_SET_DEVICE_FORMATS ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int SST_HSW_DEVICE_TDM_CLOCK_MASTER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hsw_device_config_req (struct sst_hsw_ipc_device_config_req*) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int) ; 

int sst_hsw_device_set_config(struct sst_hsw *hsw,
	enum sst_hsw_device_id dev, enum sst_hsw_device_mclk mclk,
	enum sst_hsw_device_mode mode, u32 clock_divider)
{
	struct sst_ipc_message request;
	struct sst_hsw_ipc_device_config_req config;
	int ret;

	trace_ipc_request("set device config", dev);

	hsw->dx_dev = config.ssp_interface = dev;
	hsw->dx_mclk = config.clock_frequency = mclk;
	hsw->dx_mode = config.mode = mode;
	hsw->dx_clock_divider = config.clock_divider = clock_divider;
	if (mode == SST_HSW_DEVICE_TDM_CLOCK_MASTER)
		config.channels = 4;
	else
		config.channels = 2;

	trace_hsw_device_config_req(&config);

	request.header = IPC_GLB_TYPE(IPC_GLB_SET_DEVICE_FORMATS);
	request.data = &config;
	request.size = sizeof(config);

	ret = sst_ipc_tx_message_wait(&hsw->ipc, request, NULL);
	if (ret < 0)
		dev_err(hsw->dev, "error: set device formats failed\n");

	return ret;
}
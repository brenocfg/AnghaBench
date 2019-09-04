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
typedef  int u32 ;
struct sst_hsw_ipc_dx_reply {int entries_no; TYPE_1__* mem_info; } ;
struct sst_hsw {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
typedef  int /*<<< orphan*/  state_ ;
typedef  enum sst_hsw_dx_state { ____Placeholder_sst_hsw_dx_state } sst_hsw_dx_state ;
struct TYPE_2__ {int /*<<< orphan*/  source; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_GLB_ENTER_DX_STATE ; 
 int IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,int,int*,int,struct sst_hsw_ipc_dx_reply*,int) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int) ; 

int sst_hsw_dx_set_state(struct sst_hsw *hsw,
	enum sst_hsw_dx_state state, struct sst_hsw_ipc_dx_reply *dx)
{
	u32 header, state_;
	int ret, item;

	header = IPC_GLB_TYPE(IPC_GLB_ENTER_DX_STATE);
	state_ = state;

	trace_ipc_request("PM enter Dx state", state);

	ret = sst_ipc_tx_message_wait(&hsw->ipc, header, &state_,
		sizeof(state_), dx, sizeof(*dx));
	if (ret < 0) {
		dev_err(hsw->dev, "ipc: error set dx state %d failed\n", state);
		return ret;
	}

	for (item = 0; item < dx->entries_no; item++) {
		dev_dbg(hsw->dev,
			"Item[%d] offset[%x] - size[%x] - source[%x]\n",
			item, dx->mem_info[item].offset,
			dx->mem_info[item].size,
			dx->mem_info[item].source);
	}
	dev_dbg(hsw->dev, "ipc: got %d entry numbers for state %d\n",
		dx->entries_no, state);

	return ret;
}
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
struct wkup_m3_ipc {int resume_addr; int mem_type; int /*<<< orphan*/  state; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DS_IPC_DEFAULT ; 
 int ENODEV ; 
 int IPC_CMD_DS0 ; 
 int IPC_CMD_IDLE ; 
 int IPC_CMD_STANDBY ; 
 int /*<<< orphan*/  M3_STATE_MSG_FOR_LP ; 
#define  WKUP_M3_DEEPSLEEP 130 
#define  WKUP_M3_IDLE 129 
#define  WKUP_M3_STANDBY 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  wkup_m3_ctrl_ipc_write (struct wkup_m3_ipc*,int,int) ; 
 int /*<<< orphan*/  wkup_m3_is_available (struct wkup_m3_ipc*) ; 
 int wkup_m3_ping (struct wkup_m3_ipc*) ; 
 int wkup_m3_ping_noirq (struct wkup_m3_ipc*) ; 

__attribute__((used)) static int wkup_m3_prepare_low_power(struct wkup_m3_ipc *m3_ipc, int state)
{
	struct device *dev = m3_ipc->dev;
	int m3_power_state;
	int ret = 0;

	if (!wkup_m3_is_available(m3_ipc))
		return -ENODEV;

	switch (state) {
	case WKUP_M3_DEEPSLEEP:
		m3_power_state = IPC_CMD_DS0;
		break;
	case WKUP_M3_STANDBY:
		m3_power_state = IPC_CMD_STANDBY;
		break;
	case WKUP_M3_IDLE:
		m3_power_state = IPC_CMD_IDLE;
		break;
	default:
		return 1;
	}

	/* Program each required IPC register then write defaults to others */
	wkup_m3_ctrl_ipc_write(m3_ipc, m3_ipc->resume_addr, 0);
	wkup_m3_ctrl_ipc_write(m3_ipc, m3_power_state, 1);
	wkup_m3_ctrl_ipc_write(m3_ipc, m3_ipc->mem_type, 4);

	wkup_m3_ctrl_ipc_write(m3_ipc, DS_IPC_DEFAULT, 2);
	wkup_m3_ctrl_ipc_write(m3_ipc, DS_IPC_DEFAULT, 3);
	wkup_m3_ctrl_ipc_write(m3_ipc, DS_IPC_DEFAULT, 5);
	wkup_m3_ctrl_ipc_write(m3_ipc, DS_IPC_DEFAULT, 6);
	wkup_m3_ctrl_ipc_write(m3_ipc, DS_IPC_DEFAULT, 7);

	m3_ipc->state = M3_STATE_MSG_FOR_LP;

	if (state == WKUP_M3_IDLE)
		ret = wkup_m3_ping_noirq(m3_ipc);
	else
		ret = wkup_m3_ping(m3_ipc);

	if (ret) {
		dev_err(dev, "Unable to ping CM3\n");
		return ret;
	}

	return 0;
}
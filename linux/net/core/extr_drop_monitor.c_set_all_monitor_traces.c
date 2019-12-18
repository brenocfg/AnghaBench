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
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
#define  TRACE_OFF 129 
#define  TRACE_ON 128 
 int /*<<< orphan*/  net_dm_trace_off_set () ; 
 int net_dm_trace_on_set (struct netlink_ext_ack*) ; 
 int trace_state ; 

__attribute__((used)) static int set_all_monitor_traces(int state, struct netlink_ext_ack *extack)
{
	int rc = 0;

	if (state == trace_state) {
		NL_SET_ERR_MSG_MOD(extack, "Trace state already set to requested state");
		return -EAGAIN;
	}

	switch (state) {
	case TRACE_ON:
		rc = net_dm_trace_on_set(extack);
		break;
	case TRACE_OFF:
		net_dm_trace_off_set();
		break;
	default:
		rc = 1;
		break;
	}

	if (!rc)
		trace_state = state;
	else
		rc = -EINPROGRESS;

	return rc;
}
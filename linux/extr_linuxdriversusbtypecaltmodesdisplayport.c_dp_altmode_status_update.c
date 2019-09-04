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
typedef  int u8 ;
struct TYPE_2__ {int status; scalar_t__ conf; } ;
struct dp_altmode {void* state; TYPE_1__ data; } ;

/* Variables and functions */
 int DP_CONF_CURRENTLY (scalar_t__) ; 
 int /*<<< orphan*/  DP_CONF_GET_PIN_ASSIGN (scalar_t__) ; 
 void* DP_STATE_CONFIGURE ; 
 void* DP_STATE_EXIT ; 
 int DP_STATUS_CONNECTION (int) ; 
 int DP_STATUS_EXIT_DP_MODE ; 
 int DP_STATUS_SWITCH_TO_USB ; 
 int dp_altmode_configure (struct dp_altmode*,int) ; 

__attribute__((used)) static int dp_altmode_status_update(struct dp_altmode *dp)
{
	bool configured = !!DP_CONF_GET_PIN_ASSIGN(dp->data.conf);
	u8 con = DP_STATUS_CONNECTION(dp->data.status);
	int ret = 0;

	if (configured && (dp->data.status & DP_STATUS_SWITCH_TO_USB)) {
		dp->data.conf = 0;
		dp->state = DP_STATE_CONFIGURE;
	} else if (dp->data.status & DP_STATUS_EXIT_DP_MODE) {
		dp->state = DP_STATE_EXIT;
	} else if (!(con & DP_CONF_CURRENTLY(dp->data.conf))) {
		ret = dp_altmode_configure(dp, con);
		if (!ret)
			dp->state = DP_STATE_CONFIGURE;
	}

	return ret;
}
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
struct rndis_params {int /*<<< orphan*/  media_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNDIS_MEDIA_STATE_CONNECTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_MEDIA_CONNECT ; 
 int rndis_indicate_status_msg (struct rndis_params*,int /*<<< orphan*/ ) ; 

int rndis_signal_connect(struct rndis_params *params)
{
	params->media_state = RNDIS_MEDIA_STATE_CONNECTED;
	return rndis_indicate_status_msg(params, RNDIS_STATUS_MEDIA_CONNECT);
}
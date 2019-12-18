#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union smcd_sw_event_info {int /*<<< orphan*/  info; int /*<<< orphan*/  code; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  uid; } ;
struct smc_link_group {int /*<<< orphan*/  peer_gid; TYPE_2__* smcd; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* signal_event ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISM_EVENT_CODE_SHUTDOWN ; 
 int /*<<< orphan*/  ISM_EVENT_REQUEST ; 
 int /*<<< orphan*/  ISM_EVENT_REQUEST_IR ; 
 int /*<<< orphan*/  SMC_LGR_ID_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smc_ism_signal_shutdown(struct smc_link_group *lgr)
{
	int rc;
	union smcd_sw_event_info ev_info;

	memcpy(ev_info.uid, lgr->id, SMC_LGR_ID_SIZE);
	ev_info.vlan_id = lgr->vlan_id;
	ev_info.code = ISM_EVENT_REQUEST;
	rc = lgr->smcd->ops->signal_event(lgr->smcd, lgr->peer_gid,
					  ISM_EVENT_REQUEST_IR,
					  ISM_EVENT_CODE_SHUTDOWN,
					  ev_info.info);
	return rc;
}
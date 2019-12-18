#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union smcd_sw_event_info {int /*<<< orphan*/  info; int /*<<< orphan*/  code; int /*<<< orphan*/  vlan_id; } ;
struct TYPE_6__ {int code; int /*<<< orphan*/  tok; int /*<<< orphan*/  info; } ;
struct smc_ism_event_work {TYPE_2__ event; TYPE_3__* smcd; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* signal_event ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  ISM_EVENT_CODE_SHUTDOWN 129 
#define  ISM_EVENT_CODE_TESTLINK 128 
 int /*<<< orphan*/  ISM_EVENT_REQUEST ; 
 int /*<<< orphan*/  ISM_EVENT_REQUEST_IR ; 
 int /*<<< orphan*/  ISM_EVENT_RESPONSE ; 
 int /*<<< orphan*/  smc_smcd_terminate (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smcd_handle_sw_event(struct smc_ism_event_work *wrk)
{
	union smcd_sw_event_info ev_info;

	ev_info.info = wrk->event.info;
	switch (wrk->event.code) {
	case ISM_EVENT_CODE_SHUTDOWN:	/* Peer shut down DMBs */
		smc_smcd_terminate(wrk->smcd, wrk->event.tok, ev_info.vlan_id);
		break;
	case ISM_EVENT_CODE_TESTLINK:	/* Activity timer */
		if (ev_info.code == ISM_EVENT_REQUEST) {
			ev_info.code = ISM_EVENT_RESPONSE;
			wrk->smcd->ops->signal_event(wrk->smcd,
						     wrk->event.tok,
						     ISM_EVENT_REQUEST_IR,
						     ISM_EVENT_CODE_TESTLINK,
						     ev_info.info);
			}
		break;
	}
}
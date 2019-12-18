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
typedef  int /*<<< orphan*/  u8 ;
struct smc_link {struct smc_ib_device* smcibdev; } ;
struct smc_ib_device {int /*<<< orphan*/  port_event_work; int /*<<< orphan*/  port_event_mask; } ;
struct TYPE_4__ {TYPE_1__* qp; } ;
struct ib_event {int event; TYPE_2__ element; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
#define  IB_EVENT_QP_ACCESS_ERR 129 
#define  IB_EVENT_QP_FATAL 128 
 int /*<<< orphan*/  SMC_MAX_PORTS ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smc_ib_qp_event_handler(struct ib_event *ibevent, void *priv)
{
	struct smc_link *lnk = (struct smc_link *)priv;
	struct smc_ib_device *smcibdev = lnk->smcibdev;
	u8 port_idx;

	switch (ibevent->event) {
	case IB_EVENT_QP_FATAL:
	case IB_EVENT_QP_ACCESS_ERR:
		port_idx = ibevent->element.qp->port - 1;
		if (port_idx < SMC_MAX_PORTS) {
			set_bit(port_idx, &smcibdev->port_event_mask);
			schedule_work(&smcibdev->port_event_work);
		}
		break;
	default:
		break;
	}
}
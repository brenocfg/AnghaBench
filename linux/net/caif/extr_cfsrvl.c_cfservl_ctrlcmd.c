#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int id; } ;
struct cfsrvl {int open; int modem_flow_on; int phy_flow_on; TYPE_1__ dev_info; } ;
struct cflayer {TYPE_2__* up; } ;
typedef  enum caif_ctrlcmd { ____Placeholder_caif_ctrlcmd } caif_ctrlcmd ;
struct TYPE_12__ {int /*<<< orphan*/  (* ctrlcmd ) (TYPE_2__*,int,int) ;} ;

/* Variables and functions */
#define  CAIF_CTRLCMD_DEINIT_RSP 136 
#define  CAIF_CTRLCMD_FLOW_OFF_IND 135 
#define  CAIF_CTRLCMD_FLOW_ON_IND 134 
#define  CAIF_CTRLCMD_INIT_FAIL_RSP 133 
#define  CAIF_CTRLCMD_INIT_RSP 132 
#define  CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND 131 
#define  _CAIF_CTRLCMD_PHYIF_DOWN_IND 130 
#define  _CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND 129 
#define  _CAIF_CTRLCMD_PHYIF_FLOW_ON_IND 128 
 struct cfsrvl* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int const,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int const,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub9 (TYPE_2__*,int,int) ; 

__attribute__((used)) static void cfservl_ctrlcmd(struct cflayer *layr, enum caif_ctrlcmd ctrl,
			    int phyid)
{
	struct cfsrvl *service = container_obj(layr);

	if (layr->up == NULL || layr->up->ctrlcmd == NULL)
		return;

	switch (ctrl) {
	case CAIF_CTRLCMD_INIT_RSP:
		service->open = true;
		layr->up->ctrlcmd(layr->up, ctrl, phyid);
		break;
	case CAIF_CTRLCMD_DEINIT_RSP:
	case CAIF_CTRLCMD_INIT_FAIL_RSP:
		service->open = false;
		layr->up->ctrlcmd(layr->up, ctrl, phyid);
		break;
	case _CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND:
		if (phyid != service->dev_info.id)
			break;
		if (service->modem_flow_on)
			layr->up->ctrlcmd(layr->up,
					  CAIF_CTRLCMD_FLOW_OFF_IND, phyid);
		service->phy_flow_on = false;
		break;
	case _CAIF_CTRLCMD_PHYIF_FLOW_ON_IND:
		if (phyid != service->dev_info.id)
			return;
		if (service->modem_flow_on) {
			layr->up->ctrlcmd(layr->up,
					   CAIF_CTRLCMD_FLOW_ON_IND,
					   phyid);
		}
		service->phy_flow_on = true;
		break;
	case CAIF_CTRLCMD_FLOW_OFF_IND:
		if (service->phy_flow_on) {
			layr->up->ctrlcmd(layr->up,
					  CAIF_CTRLCMD_FLOW_OFF_IND, phyid);
		}
		service->modem_flow_on = false;
		break;
	case CAIF_CTRLCMD_FLOW_ON_IND:
		if (service->phy_flow_on) {
			layr->up->ctrlcmd(layr->up,
					  CAIF_CTRLCMD_FLOW_ON_IND, phyid);
		}
		service->modem_flow_on = true;
		break;
	case _CAIF_CTRLCMD_PHYIF_DOWN_IND:
		/* In case interface is down, let's fake a remove shutdown */
		layr->up->ctrlcmd(layr->up,
				CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND, phyid);
		break;
	case CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND:
		layr->up->ctrlcmd(layr->up, ctrl, phyid);
		break;
	default:
		pr_warn("Unexpected ctrl in cfsrvl (%d)\n", ctrl);
		/* We have both modem and phy flow on, send flow on */
		layr->up->ctrlcmd(layr->up, ctrl, phyid);
		service->phy_flow_on = true;
		break;
	}
}
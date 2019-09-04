#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sent_enbdis; } ;
struct visornic_devdata {TYPE_2__ chstat; TYPE_5__* cmdrsp_rcv; TYPE_1__* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {int enable; struct net_device* context; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; TYPE_4__ enbdis; } ;
struct TYPE_10__ {int /*<<< orphan*/  cmdtype; TYPE_3__ net; } ;
struct TYPE_6__ {int /*<<< orphan*/  visorchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_NET_TYPE ; 
 int /*<<< orphan*/  IOCHAN_TO_IOPART ; 
 int /*<<< orphan*/  NET_RCV_ENBDIS ; 
 int visorchannel_signalinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int send_enbdis(struct net_device *netdev, int state,
		       struct visornic_devdata *devdata)
{
	int err;

	devdata->cmdrsp_rcv->net.enbdis.enable = state;
	devdata->cmdrsp_rcv->net.enbdis.context = netdev;
	devdata->cmdrsp_rcv->net.type = NET_RCV_ENBDIS;
	devdata->cmdrsp_rcv->cmdtype = CMD_NET_TYPE;
	err = visorchannel_signalinsert(devdata->dev->visorchannel,
					IOCHAN_TO_IOPART,
					devdata->cmdrsp_rcv);
	if (err)
		return err;
	devdata->chstat.sent_enbdis++;
	return 0;
}
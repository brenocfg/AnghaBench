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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct cfsrvl {int /*<<< orphan*/  dev_info; TYPE_1__ layer; } ;
struct cfpkt {int dummy; } ;
struct cflayer {TYPE_2__* dn; } ;
struct caif_payload_info {int /*<<< orphan*/ * dev_info; int /*<<< orphan*/  channel_id; } ;
struct TYPE_4__ {int (* transmit ) (TYPE_2__*,struct cfpkt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 struct caif_payload_info* cfpkt_info (struct cfpkt*) ; 
 int /*<<< orphan*/  cfsrvl_ready (struct cfsrvl*,int*) ; 
 struct cfsrvl* container_obj (struct cflayer*) ; 
 int stub1 (TYPE_2__*,struct cfpkt*) ; 

__attribute__((used)) static int cfdbgl_transmit(struct cflayer *layr, struct cfpkt *pkt)
{
	struct cfsrvl *service = container_obj(layr);
	struct caif_payload_info *info;
	int ret;

	if (!cfsrvl_ready(service, &ret)) {
		cfpkt_destroy(pkt);
		return ret;
	}

	/* Add info for MUX-layer to route the packet out */
	info = cfpkt_info(pkt);
	info->channel_id = service->layer.id;
	info->dev_info = &service->dev_info;

	return layr->dn->transmit(layr->dn, pkt);
}
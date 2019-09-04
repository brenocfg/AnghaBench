#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct cfsrvl {int /*<<< orphan*/  dev_info; TYPE_1__ layer; int /*<<< orphan*/  supports_flowctrl; } ;
struct cfpkt {int dummy; } ;
struct cflayer {TYPE_2__* dn; } ;
struct caif_payload_info {int hdr_len; int /*<<< orphan*/ * dev_info; int /*<<< orphan*/  channel_id; } ;
typedef  enum caif_modemcmd { ____Placeholder_caif_modemcmd } caif_modemcmd ;
struct TYPE_5__ {int (* transmit ) (TYPE_2__*,struct cfpkt*) ;} ;

/* Variables and functions */
#define  CAIF_MODEMCMD_FLOW_OFF_REQ 129 
#define  CAIF_MODEMCMD_FLOW_ON_REQ 128 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  SRVL_CTRL_PKT_SIZE ; 
 int /*<<< orphan*/  SRVL_FLOW_OFF ; 
 int /*<<< orphan*/  SRVL_FLOW_ON ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_add_head (struct cfpkt*,int /*<<< orphan*/ *,int) ; 
 struct cfpkt* cfpkt_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 struct caif_payload_info* cfpkt_info (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_set_prio (struct cfpkt*,int /*<<< orphan*/ ) ; 
 struct cfsrvl* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (TYPE_2__*,struct cfpkt*) ; 
 int stub2 (TYPE_2__*,struct cfpkt*) ; 

__attribute__((used)) static int cfservl_modemcmd(struct cflayer *layr, enum caif_modemcmd ctrl)
{
	struct cfsrvl *service = container_obj(layr);

	caif_assert(layr != NULL);
	caif_assert(layr->dn != NULL);
	caif_assert(layr->dn->transmit != NULL);

	if (!service->supports_flowctrl)
		return 0;

	switch (ctrl) {
	case CAIF_MODEMCMD_FLOW_ON_REQ:
		{
			struct cfpkt *pkt;
			struct caif_payload_info *info;
			u8 flow_on = SRVL_FLOW_ON;
			pkt = cfpkt_create(SRVL_CTRL_PKT_SIZE);
			if (!pkt)
				return -ENOMEM;

			if (cfpkt_add_head(pkt, &flow_on, 1) < 0) {
				pr_err("Packet is erroneous!\n");
				cfpkt_destroy(pkt);
				return -EPROTO;
			}
			info = cfpkt_info(pkt);
			info->channel_id = service->layer.id;
			info->hdr_len = 1;
			info->dev_info = &service->dev_info;
			cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
			return layr->dn->transmit(layr->dn, pkt);
		}
	case CAIF_MODEMCMD_FLOW_OFF_REQ:
		{
			struct cfpkt *pkt;
			struct caif_payload_info *info;
			u8 flow_off = SRVL_FLOW_OFF;
			pkt = cfpkt_create(SRVL_CTRL_PKT_SIZE);
			if (!pkt)
				return -ENOMEM;

			if (cfpkt_add_head(pkt, &flow_off, 1) < 0) {
				pr_err("Packet is erroneous!\n");
				cfpkt_destroy(pkt);
				return -EPROTO;
			}
			info = cfpkt_info(pkt);
			info->channel_id = service->layer.id;
			info->hdr_len = 1;
			info->dev_info = &service->dev_info;
			cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
			return layr->dn->transmit(layr->dn, pkt);
		}
	default:
	  break;
	}
	return -EINVAL;
}
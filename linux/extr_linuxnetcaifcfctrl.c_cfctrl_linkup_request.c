#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  utility_name ;
typedef  char u8 ;
typedef  char u32 ;
typedef  char u16 ;
struct cfpkt {int dummy; } ;
struct cflayer {int (* transmit ) (struct cflayer*,struct cfpkt*) ;struct cflayer* dn; } ;
struct TYPE_13__ {char paramlen; char* params; int /*<<< orphan*/  name; int /*<<< orphan*/  fifosize_bufs; int /*<<< orphan*/  fifosize_kb; } ;
struct TYPE_12__ {char* volume; int /*<<< orphan*/  connid; } ;
struct TYPE_11__ {int /*<<< orphan*/  connid; } ;
struct TYPE_10__ {int /*<<< orphan*/  connid; } ;
struct TYPE_14__ {TYPE_4__ utility; TYPE_3__ rfm; TYPE_2__ datagram; TYPE_1__ video; } ;
struct cfctrl_link_param {int chtype; int linktype; int priority; int phyid; int endpoint; TYPE_5__ u; } ;
struct cfctrl_request_info {char cmd; struct cfctrl_link_param param; struct cflayer* client_layer; } ;
struct TYPE_16__ {struct cflayer layer; } ;
struct cfctrl {TYPE_7__ serv; } ;
struct TYPE_17__ {TYPE_6__* dev_info; } ;
struct TYPE_15__ {int id; } ;

/* Variables and functions */
 char CFCTRL_CMD_LINK_SETUP ; 
#define  CFCTRL_SRV_DATAGRAM 133 
#define  CFCTRL_SRV_DBG 132 
#define  CFCTRL_SRV_RFM 131 
#define  CFCTRL_SRV_UTIL 130 
#define  CFCTRL_SRV_VEI 129 
#define  CFCTRL_SRV_VIDEO 128 
 int /*<<< orphan*/  CFPKT_CTRL_PKT_LEN ; 
 int EALREADY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 int UTILITY_NAME_LENGTH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int cfctrl_cancel_req (struct cflayer*,struct cflayer*) ; 
 int /*<<< orphan*/  cfctrl_insert_req (struct cfctrl*,struct cfctrl_request_info*) ; 
 int /*<<< orphan*/  cfpkt_add_body (struct cfpkt*,char*,int) ; 
 int /*<<< orphan*/  cfpkt_addbdy (struct cfpkt*,char) ; 
 struct cfpkt* cfpkt_create (int /*<<< orphan*/ ) ; 
 TYPE_8__* cfpkt_info (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_set_prio (struct cfpkt*,int /*<<< orphan*/ ) ; 
 struct cfctrl* container_obj (struct cflayer*) ; 
 char cpu_to_le16 (int /*<<< orphan*/ ) ; 
 char cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_info (TYPE_8__*,struct cfctrl*) ; 
 struct cfctrl_request_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int stub1 (struct cflayer*,struct cfpkt*) ; 

int cfctrl_linkup_request(struct cflayer *layer,
			  struct cfctrl_link_param *param,
			  struct cflayer *user_layer)
{
	struct cfctrl *cfctrl = container_obj(layer);
	u32 tmp32;
	u16 tmp16;
	u8 tmp8;
	struct cfctrl_request_info *req;
	int ret;
	char utility_name[16];
	struct cfpkt *pkt;
	struct cflayer *dn = cfctrl->serv.layer.dn;

	if (!dn) {
		pr_debug("not able to send linkup request\n");
		return -ENODEV;
	}

	if (cfctrl_cancel_req(layer, user_layer) > 0) {
		/* Slight Paranoia, check if already connecting */
		pr_err("Duplicate connect request for same client\n");
		WARN_ON(1);
		return -EALREADY;
	}

	pkt = cfpkt_create(CFPKT_CTRL_PKT_LEN);
	if (!pkt)
		return -ENOMEM;
	cfpkt_addbdy(pkt, CFCTRL_CMD_LINK_SETUP);
	cfpkt_addbdy(pkt, (param->chtype << 4) | param->linktype);
	cfpkt_addbdy(pkt, (param->priority << 3) | param->phyid);
	cfpkt_addbdy(pkt, param->endpoint & 0x03);

	switch (param->linktype) {
	case CFCTRL_SRV_VEI:
		break;
	case CFCTRL_SRV_VIDEO:
		cfpkt_addbdy(pkt, (u8) param->u.video.connid);
		break;
	case CFCTRL_SRV_DBG:
		break;
	case CFCTRL_SRV_DATAGRAM:
		tmp32 = cpu_to_le32(param->u.datagram.connid);
		cfpkt_add_body(pkt, &tmp32, 4);
		break;
	case CFCTRL_SRV_RFM:
		/* Construct a frame, convert DatagramConnectionID to network
		 * format long and copy it out...
		 */
		tmp32 = cpu_to_le32(param->u.rfm.connid);
		cfpkt_add_body(pkt, &tmp32, 4);
		/* Add volume name, including zero termination... */
		cfpkt_add_body(pkt, param->u.rfm.volume,
			       strlen(param->u.rfm.volume) + 1);
		break;
	case CFCTRL_SRV_UTIL:
		tmp16 = cpu_to_le16(param->u.utility.fifosize_kb);
		cfpkt_add_body(pkt, &tmp16, 2);
		tmp16 = cpu_to_le16(param->u.utility.fifosize_bufs);
		cfpkt_add_body(pkt, &tmp16, 2);
		memset(utility_name, 0, sizeof(utility_name));
		strlcpy(utility_name, param->u.utility.name,
			UTILITY_NAME_LENGTH);
		cfpkt_add_body(pkt, utility_name, UTILITY_NAME_LENGTH);
		tmp8 = param->u.utility.paramlen;
		cfpkt_add_body(pkt, &tmp8, 1);
		cfpkt_add_body(pkt, param->u.utility.params,
			       param->u.utility.paramlen);
		break;
	default:
		pr_warn("Request setup of bad link type = %d\n",
			param->linktype);
		return -EINVAL;
	}
	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;
	req->client_layer = user_layer;
	req->cmd = CFCTRL_CMD_LINK_SETUP;
	req->param = *param;
	cfctrl_insert_req(cfctrl, req);
	init_info(cfpkt_info(pkt), cfctrl);
	/*
	 * NOTE:Always send linkup and linkdown request on the same
	 *	device as the payload. Otherwise old queued up payload
	 *	might arrive with the newly allocated channel ID.
	 */
	cfpkt_info(pkt)->dev_info->id = param->phyid;
	cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
	ret =
	    dn->transmit(dn, pkt);
	if (ret < 0) {
		int count;

		count = cfctrl_cancel_req(&cfctrl->serv.layer,
						user_layer);
		if (count != 1) {
			pr_err("Could not remove request (%d)", count);
			return -ENODEV;
		}
	}
	return 0;
}
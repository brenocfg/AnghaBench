#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cfpkt {int dummy; } ;
struct cflayer {int dummy; } ;
struct TYPE_12__ {int paramlen; int* params; scalar_t__ name; void* fifosize_bufs; void* fifosize_kb; } ;
struct TYPE_11__ {scalar_t__ volume; void* connid; } ;
struct TYPE_10__ {void* connid; } ;
struct TYPE_9__ {int connid; } ;
struct TYPE_13__ {TYPE_4__ utility; TYPE_3__ rfm; TYPE_2__ datagram; TYPE_1__ video; } ;
struct cfctrl_link_param {int linktype; int chtype; int priority; int phyid; int endpoint; TYPE_5__ u; } ;
struct cfctrl_request_info {int cmd; int /*<<< orphan*/ * client_layer; struct cfctrl_link_param param; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* radioset_rsp ) () ;int /*<<< orphan*/  (* restart_rsp ) () ;int /*<<< orphan*/  (* wake_rsp ) () ;int /*<<< orphan*/  (* sleep_rsp ) () ;int /*<<< orphan*/  (* enum_rsp ) () ;int /*<<< orphan*/  (* linkerror_ind ) () ;int /*<<< orphan*/  (* linkdestroy_rsp ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* linksetup_rsp ) (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* reject_rsp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  up; } ;
struct TYPE_15__ {TYPE_6__ layer; } ;
struct cfctrl {TYPE_8__ res; TYPE_7__ serv; int /*<<< orphan*/  info_list_lock; } ;
typedef  int /*<<< orphan*/  linkparam ;
typedef  enum cfctrl_srv { ____Placeholder_cfctrl_srv } cfctrl_srv ;

/* Variables and functions */
#define  CFCTRL_CMD_ENUM 141 
#define  CFCTRL_CMD_LINK_DESTROY 140 
#define  CFCTRL_CMD_LINK_ERR 139 
#define  CFCTRL_CMD_LINK_RECONF 138 
#define  CFCTRL_CMD_LINK_SETUP 137 
 int CFCTRL_CMD_MASK ; 
#define  CFCTRL_CMD_RADIO_SET 136 
#define  CFCTRL_CMD_SLEEP 135 
#define  CFCTRL_CMD_WAKE 134 
 int CFCTRL_ERR_BIT ; 
 int CFCTRL_RSP_BIT ; 
#define  CFCTRL_SRV_DATAGRAM 133 
#define  CFCTRL_SRV_DBG 132 
 int CFCTRL_SRV_MASK ; 
#define  CFCTRL_SRV_RFM 131 
#define  CFCTRL_SRV_UTIL 130 
#define  CFCTRL_SRV_VEI 129 
#define  CFCTRL_SRV_VIDEO 128 
 int UTILITY_NAME_LENGTH ; 
 int /*<<< orphan*/  caif_assert (int) ; 
 struct cfctrl_request_info* cfctrl_remove_req (struct cfctrl*,struct cfctrl_request_info*) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_erroneous (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_extr_head (struct cfpkt*,int**,int) ; 
 void* cfpkt_extr_head_u16 (struct cfpkt*) ; 
 void* cfpkt_extr_head_u32 (struct cfpkt*) ; 
 int cfpkt_extr_head_u8 (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_more (struct cfpkt*) ; 
 struct cfctrl* container_obj (struct cflayer*) ; 
 scalar_t__ handle_loop (struct cfctrl*,int,struct cfpkt*) ; 
 int /*<<< orphan*/  kfree (struct cfctrl_request_info*) ; 
 int /*<<< orphan*/  memset (struct cfctrl_link_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  stub5 () ; 
 int /*<<< orphan*/  stub6 () ; 
 int /*<<< orphan*/  stub7 () ; 
 int /*<<< orphan*/  stub8 () ; 
 int /*<<< orphan*/  stub9 () ; 

__attribute__((used)) static int cfctrl_recv(struct cflayer *layer, struct cfpkt *pkt)
{
	u8 cmdrsp;
	u8 cmd;
	int ret = -1;
	u8 len;
	u8 param[255];
	u8 linkid = 0;
	struct cfctrl *cfctrl = container_obj(layer);
	struct cfctrl_request_info rsp, *req;


	cmdrsp = cfpkt_extr_head_u8(pkt);
	cmd = cmdrsp & CFCTRL_CMD_MASK;
	if (cmd != CFCTRL_CMD_LINK_ERR
	    && CFCTRL_RSP_BIT != (CFCTRL_RSP_BIT & cmdrsp)
		&& CFCTRL_ERR_BIT != (CFCTRL_ERR_BIT & cmdrsp)) {
		if (handle_loop(cfctrl, cmd, pkt) != 0)
			cmdrsp |= CFCTRL_ERR_BIT;
	}

	switch (cmd) {
	case CFCTRL_CMD_LINK_SETUP:
		{
			enum cfctrl_srv serv;
			enum cfctrl_srv servtype;
			u8 endpoint;
			u8 physlinkid;
			u8 prio;
			u8 tmp;
			u8 *cp;
			int i;
			struct cfctrl_link_param linkparam;
			memset(&linkparam, 0, sizeof(linkparam));

			tmp = cfpkt_extr_head_u8(pkt);

			serv = tmp & CFCTRL_SRV_MASK;
			linkparam.linktype = serv;

			servtype = tmp >> 4;
			linkparam.chtype = servtype;

			tmp = cfpkt_extr_head_u8(pkt);
			physlinkid = tmp & 0x07;
			prio = tmp >> 3;

			linkparam.priority = prio;
			linkparam.phyid = physlinkid;
			endpoint = cfpkt_extr_head_u8(pkt);
			linkparam.endpoint = endpoint & 0x03;

			switch (serv) {
			case CFCTRL_SRV_VEI:
			case CFCTRL_SRV_DBG:
				if (CFCTRL_ERR_BIT & cmdrsp)
					break;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);
				break;
			case CFCTRL_SRV_VIDEO:
				tmp = cfpkt_extr_head_u8(pkt);
				linkparam.u.video.connid = tmp;
				if (CFCTRL_ERR_BIT & cmdrsp)
					break;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);
				break;

			case CFCTRL_SRV_DATAGRAM:
				linkparam.u.datagram.connid =
				    cfpkt_extr_head_u32(pkt);
				if (CFCTRL_ERR_BIT & cmdrsp)
					break;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);
				break;
			case CFCTRL_SRV_RFM:
				/* Construct a frame, convert
				 * DatagramConnectionID
				 * to network format long and copy it out...
				 */
				linkparam.u.rfm.connid =
				    cfpkt_extr_head_u32(pkt);
				cp = (u8 *) linkparam.u.rfm.volume;
				for (tmp = cfpkt_extr_head_u8(pkt);
				     cfpkt_more(pkt) && tmp != '\0';
				     tmp = cfpkt_extr_head_u8(pkt))
					*cp++ = tmp;
				*cp = '\0';

				if (CFCTRL_ERR_BIT & cmdrsp)
					break;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);

				break;
			case CFCTRL_SRV_UTIL:
				/* Construct a frame, convert
				 * DatagramConnectionID
				 * to network format long and copy it out...
				 */
				/* Fifosize KB */
				linkparam.u.utility.fifosize_kb =
				    cfpkt_extr_head_u16(pkt);
				/* Fifosize bufs */
				linkparam.u.utility.fifosize_bufs =
				    cfpkt_extr_head_u16(pkt);
				/* name */
				cp = (u8 *) linkparam.u.utility.name;
				caif_assert(sizeof(linkparam.u.utility.name)
					     >= UTILITY_NAME_LENGTH);
				for (i = 0;
				     i < UTILITY_NAME_LENGTH
				     && cfpkt_more(pkt); i++) {
					tmp = cfpkt_extr_head_u8(pkt);
					*cp++ = tmp;
				}
				/* Length */
				len = cfpkt_extr_head_u8(pkt);
				linkparam.u.utility.paramlen = len;
				/* Param Data */
				cp = linkparam.u.utility.params;
				while (cfpkt_more(pkt) && len--) {
					tmp = cfpkt_extr_head_u8(pkt);
					*cp++ = tmp;
				}
				if (CFCTRL_ERR_BIT & cmdrsp)
					break;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);
				/* Length */
				len = cfpkt_extr_head_u8(pkt);
				/* Param Data */
				cfpkt_extr_head(pkt, &param, len);
				break;
			default:
				pr_warn("Request setup, invalid type (%d)\n",
					serv);
				goto error;
			}

			rsp.cmd = cmd;
			rsp.param = linkparam;
			spin_lock_bh(&cfctrl->info_list_lock);
			req = cfctrl_remove_req(cfctrl, &rsp);

			if (CFCTRL_ERR_BIT == (CFCTRL_ERR_BIT & cmdrsp) ||
				cfpkt_erroneous(pkt)) {
				pr_err("Invalid O/E bit or parse error "
						"on CAIF control channel\n");
				cfctrl->res.reject_rsp(cfctrl->serv.layer.up,
						       0,
						       req ? req->client_layer
						       : NULL);
			} else {
				cfctrl->res.linksetup_rsp(cfctrl->serv.
							  layer.up, linkid,
							  serv, physlinkid,
							  req ? req->
							  client_layer : NULL);
			}

			kfree(req);

			spin_unlock_bh(&cfctrl->info_list_lock);
		}
		break;
	case CFCTRL_CMD_LINK_DESTROY:
		linkid = cfpkt_extr_head_u8(pkt);
		cfctrl->res.linkdestroy_rsp(cfctrl->serv.layer.up, linkid);
		break;
	case CFCTRL_CMD_LINK_ERR:
		pr_err("Frame Error Indication received\n");
		cfctrl->res.linkerror_ind();
		break;
	case CFCTRL_CMD_ENUM:
		cfctrl->res.enum_rsp();
		break;
	case CFCTRL_CMD_SLEEP:
		cfctrl->res.sleep_rsp();
		break;
	case CFCTRL_CMD_WAKE:
		cfctrl->res.wake_rsp();
		break;
	case CFCTRL_CMD_LINK_RECONF:
		cfctrl->res.restart_rsp();
		break;
	case CFCTRL_CMD_RADIO_SET:
		cfctrl->res.radioset_rsp();
		break;
	default:
		pr_err("Unrecognized Control Frame\n");
		goto error;
	}
	ret = 0;
error:
	cfpkt_destroy(pkt);
	return ret;
}
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
typedef  size_t u8 ;
struct cfpkt {int dummy; } ;
struct cflayer {int (* transmit ) (struct cflayer*,struct cfpkt*) ;} ;
struct TYPE_3__ {struct cflayer* dn; } ;
struct TYPE_4__ {TYPE_1__ layer; } ;
struct cfctrl {scalar_t__* loop_linkused; TYPE_2__ serv; } ;

/* Variables and functions */
 size_t CFCTRL_CMD_LINK_DESTROY ; 
 int /*<<< orphan*/  CFPKT_CTRL_PKT_LEN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 int /*<<< orphan*/  cfpkt_addbdy (struct cfpkt*,size_t) ; 
 struct cfpkt* cfpkt_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_info (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_set_prio (struct cfpkt*,int /*<<< orphan*/ ) ; 
 struct cfctrl* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  init_info (int /*<<< orphan*/ ,struct cfctrl*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int stub1 (struct cflayer*,struct cfpkt*) ; 

int cfctrl_linkdown_req(struct cflayer *layer, u8 channelid,
			struct cflayer *client)
{
	int ret;
	struct cfpkt *pkt;
	struct cfctrl *cfctrl = container_obj(layer);
	struct cflayer *dn = cfctrl->serv.layer.dn;

	if (!dn) {
		pr_debug("not able to send link-down request\n");
		return -ENODEV;
	}
	pkt = cfpkt_create(CFPKT_CTRL_PKT_LEN);
	if (!pkt)
		return -ENOMEM;
	cfpkt_addbdy(pkt, CFCTRL_CMD_LINK_DESTROY);
	cfpkt_addbdy(pkt, channelid);
	init_info(cfpkt_info(pkt), cfctrl);
	cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
	ret =
	    dn->transmit(dn, pkt);
#ifndef CAIF_NO_LOOP
	cfctrl->loop_linkused[channelid] = 0;
#endif
	return ret;
}
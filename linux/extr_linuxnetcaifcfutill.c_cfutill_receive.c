#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct cfsrvl {int open; } ;
struct cfpkt {int dummy; } ;
struct cflayer {int /*<<< orphan*/  (* ctrlcmd ) (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* up; } ;
struct TYPE_2__ {int (* receive ) (TYPE_1__*,struct cfpkt*) ;int /*<<< orphan*/ * ctrlcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_CTRLCMD_FLOW_OFF_IND ; 
 int /*<<< orphan*/  CAIF_CTRLCMD_FLOW_ON_IND ; 
 int /*<<< orphan*/  CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND ; 
 int EPROTO ; 
#define  UTIL_FLOW_OFF 131 
#define  UTIL_FLOW_ON 130 
#define  UTIL_PAYLOAD 129 
#define  UTIL_REMOTE_SHUTDOWN 128 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ cfpkt_extr_head (struct cfpkt*,int*,int) ; 
 struct cfsrvl* container_obj (struct cflayer*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int stub1 (TYPE_1__*,struct cfpkt*) ; 
 int /*<<< orphan*/  stub2 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfutill_receive(struct cflayer *layr, struct cfpkt *pkt)
{
	u8 cmd = -1;
	struct cfsrvl *service = container_obj(layr);
	caif_assert(layr != NULL);
	caif_assert(layr->up != NULL);
	caif_assert(layr->up->receive != NULL);
	caif_assert(layr->up->ctrlcmd != NULL);
	if (cfpkt_extr_head(pkt, &cmd, 1) < 0) {
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		return -EPROTO;
	}

	switch (cmd) {
	case UTIL_PAYLOAD:
		return layr->up->receive(layr->up, pkt);
	case UTIL_FLOW_OFF:
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_OFF_IND, 0);
		cfpkt_destroy(pkt);
		return 0;
	case UTIL_FLOW_ON:
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_ON_IND, 0);
		cfpkt_destroy(pkt);
		return 0;
	case UTIL_REMOTE_SHUTDOWN:	/* Remote Shutdown Request */
		pr_err("REMOTE SHUTDOWN REQUEST RECEIVED\n");
		layr->ctrlcmd(layr, CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND, 0);
		service->open = false;
		cfpkt_destroy(pkt);
		return 0;
	default:
		cfpkt_destroy(pkt);
		pr_warn("Unknown service control %d (0x%x)\n", cmd, cmd);
		return -EPROTO;
	}
}
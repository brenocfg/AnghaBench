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
struct cfpkt {int dummy; } ;
struct cflayer {int /*<<< orphan*/  (* ctrlcmd ) (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* up; int /*<<< orphan*/ * receive; } ;
struct TYPE_2__ {int (* receive ) (TYPE_1__*,struct cfpkt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_CTRLCMD_FLOW_OFF_IND ; 
 int /*<<< orphan*/  CAIF_CTRLCMD_FLOW_ON_IND ; 
 int EPROTO ; 
#define  VEI_FLOW_OFF 131 
#define  VEI_FLOW_ON 130 
#define  VEI_PAYLOAD 129 
#define  VEI_SET_PIN 128 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ cfpkt_extr_head (struct cfpkt*,int*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int stub1 (TYPE_1__*,struct cfpkt*) ; 
 int /*<<< orphan*/  stub2 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfvei_receive(struct cflayer *layr, struct cfpkt *pkt)
{
	u8 cmd;
	int ret;
	caif_assert(layr->up != NULL);
	caif_assert(layr->receive != NULL);
	caif_assert(layr->ctrlcmd != NULL);


	if (cfpkt_extr_head(pkt, &cmd, 1) < 0) {
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		return -EPROTO;
	}
	switch (cmd) {
	case VEI_PAYLOAD:
		ret = layr->up->receive(layr->up, pkt);
		return ret;
	case VEI_FLOW_OFF:
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_OFF_IND, 0);
		cfpkt_destroy(pkt);
		return 0;
	case VEI_FLOW_ON:
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_ON_IND, 0);
		cfpkt_destroy(pkt);
		return 0;
	case VEI_SET_PIN:	/* SET RS232 PIN */
		cfpkt_destroy(pkt);
		return 0;
	default:		/* SET RS232 PIN */
		pr_warn("Unknown VEI control packet %d (0x%x)!\n", cmd, cmd);
		cfpkt_destroy(pkt);
		return -EPROTO;
	}
}
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
 int DGM_CMD_BIT ; 
#define  DGM_FLOW_OFF 129 
#define  DGM_FLOW_ON 128 
 int EPROTO ; 
 int /*<<< orphan*/  caif_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ cfpkt_extr_head (struct cfpkt*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int stub1 (TYPE_1__*,struct cfpkt*) ; 
 int /*<<< orphan*/  stub2 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct cflayer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfdgml_receive(struct cflayer *layr, struct cfpkt *pkt)
{
	u8 cmd = -1;
	u8 dgmhdr[3];
	int ret;
	caif_assert(layr->up != NULL);
	caif_assert(layr->receive != NULL);
	caif_assert(layr->ctrlcmd != NULL);

	if (cfpkt_extr_head(pkt, &cmd, 1) < 0) {
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		return -EPROTO;
	}

	if ((cmd & DGM_CMD_BIT) == 0) {
		if (cfpkt_extr_head(pkt, &dgmhdr, 3) < 0) {
			pr_err("Packet is erroneous!\n");
			cfpkt_destroy(pkt);
			return -EPROTO;
		}
		ret = layr->up->receive(layr->up, pkt);
		return ret;
	}

	switch (cmd) {
	case DGM_FLOW_OFF:	/* FLOW OFF */
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_OFF_IND, 0);
		cfpkt_destroy(pkt);
		return 0;
	case DGM_FLOW_ON:	/* FLOW ON */
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_ON_IND, 0);
		cfpkt_destroy(pkt);
		return 0;
	default:
		cfpkt_destroy(pkt);
		pr_info("Unknown datagram control %d (0x%x)\n", cmd, cmd);
		return -EPROTO;
	}
}
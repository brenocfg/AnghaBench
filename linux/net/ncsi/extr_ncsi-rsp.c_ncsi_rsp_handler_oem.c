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
struct ncsi_rsp_oem_pkt {int /*<<< orphan*/  mfr_id; } ;
struct ncsi_rsp_oem_handler {unsigned int mfr_id; int (* handler ) (struct ncsi_request*) ;} ;
struct ncsi_request {TYPE_2__* ndp; int /*<<< orphan*/  rsp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ ndev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct ncsi_rsp_oem_handler*) ; 
 int ENOENT ; 
 struct ncsi_rsp_oem_handler* ncsi_rsp_oem_handlers ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 
 int stub1 (struct ncsi_request*) ; 

__attribute__((used)) static int ncsi_rsp_handler_oem(struct ncsi_request *nr)
{
	struct ncsi_rsp_oem_handler *nrh = NULL;
	struct ncsi_rsp_oem_pkt *rsp;
	unsigned int mfr_id, i;

	/* Get the response header */
	rsp = (struct ncsi_rsp_oem_pkt *)skb_network_header(nr->rsp);
	mfr_id = ntohl(rsp->mfr_id);

	/* Check for manufacturer id and Find the handler */
	for (i = 0; i < ARRAY_SIZE(ncsi_rsp_oem_handlers); i++) {
		if (ncsi_rsp_oem_handlers[i].mfr_id == mfr_id) {
			if (ncsi_rsp_oem_handlers[i].handler)
				nrh = &ncsi_rsp_oem_handlers[i];
			else
				nrh = NULL;

			break;
		}
	}

	if (!nrh) {
		netdev_err(nr->ndp->ndev.dev, "Received unrecognized OEM packet with MFR-ID (0x%x)\n",
			   mfr_id);
		return -ENOENT;
	}

	/* Process the packet */
	return nrh->handler(nr);
}
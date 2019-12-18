#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ncsi_rsp_oem_pkt {scalar_t__ data; } ;
struct ncsi_rsp_oem_bcm_pkt {scalar_t__ type; } ;
struct ncsi_request {int /*<<< orphan*/  rsp; } ;

/* Variables and functions */
 scalar_t__ NCSI_OEM_BCM_CMD_GMA ; 
 int ncsi_rsp_handler_oem_bcm_gma (struct ncsi_request*) ; 
 scalar_t__ skb_network_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_rsp_handler_oem_bcm(struct ncsi_request *nr)
{
	struct ncsi_rsp_oem_bcm_pkt *bcm;
	struct ncsi_rsp_oem_pkt *rsp;

	/* Get the response header */
	rsp = (struct ncsi_rsp_oem_pkt *)skb_network_header(nr->rsp);
	bcm = (struct ncsi_rsp_oem_bcm_pkt *)(rsp->data);

	if (bcm->type == NCSI_OEM_BCM_CMD_GMA)
		return ncsi_rsp_handler_oem_bcm_gma(nr);
	return 0;
}
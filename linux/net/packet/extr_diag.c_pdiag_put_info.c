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
struct sk_buff {int dummy; } ;
struct packet_sock {scalar_t__ tp_loss; scalar_t__ has_vnet_hdr; scalar_t__ origdev; scalar_t__ auxdata; scalar_t__ running; int /*<<< orphan*/  tp_tstamp; int /*<<< orphan*/  copy_thresh; int /*<<< orphan*/  tp_reserve; int /*<<< orphan*/  tp_version; int /*<<< orphan*/  ifindex; } ;
struct packet_diag_info {int /*<<< orphan*/  pdi_flags; int /*<<< orphan*/  pdi_tstamp; int /*<<< orphan*/  pdi_copy_thresh; int /*<<< orphan*/  pdi_reserve; int /*<<< orphan*/  pdi_version; int /*<<< orphan*/  pdi_index; } ;
typedef  int /*<<< orphan*/  pinfo ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_DIAG_INFO ; 
 int /*<<< orphan*/  PDI_AUXDATA ; 
 int /*<<< orphan*/  PDI_LOSS ; 
 int /*<<< orphan*/  PDI_ORIGDEV ; 
 int /*<<< orphan*/  PDI_RUNNING ; 
 int /*<<< orphan*/  PDI_VNETHDR ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct packet_diag_info*) ; 

__attribute__((used)) static int pdiag_put_info(const struct packet_sock *po, struct sk_buff *nlskb)
{
	struct packet_diag_info pinfo;

	pinfo.pdi_index = po->ifindex;
	pinfo.pdi_version = po->tp_version;
	pinfo.pdi_reserve = po->tp_reserve;
	pinfo.pdi_copy_thresh = po->copy_thresh;
	pinfo.pdi_tstamp = po->tp_tstamp;

	pinfo.pdi_flags = 0;
	if (po->running)
		pinfo.pdi_flags |= PDI_RUNNING;
	if (po->auxdata)
		pinfo.pdi_flags |= PDI_AUXDATA;
	if (po->origdev)
		pinfo.pdi_flags |= PDI_ORIGDEV;
	if (po->has_vnet_hdr)
		pinfo.pdi_flags |= PDI_VNETHDR;
	if (po->tp_loss)
		pinfo.pdi_flags |= PDI_LOSS;

	return nla_put(nlskb, PACKET_DIAG_INFO, sizeof(pinfo), &pinfo);
}
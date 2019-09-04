#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int bbCreditLsb; int bbCreditMsb; } ;
struct TYPE_8__ {TYPE_1__ cmn; } ;
struct lpfc_vport {TYPE_5__* phba; TYPE_2__ fc_sparam; } ;
struct TYPE_12__ {scalar_t__ rtt; void* attached_port_bbc; void* port_bbc; } ;
struct fc_rdp_bbc_desc {void* length; TYPE_6__ bbc_info; void* tag; } ;
struct TYPE_9__ {int bbCreditLsb; int bbCreditMsb; } ;
struct TYPE_10__ {TYPE_3__ cmn; } ;
struct TYPE_11__ {scalar_t__ fc_topology; TYPE_4__ fc_fabparam; } ;
typedef  int /*<<< orphan*/  READ_LNK_VAR ;

/* Variables and functions */
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int RDP_BBC_DESC_TAG ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static uint32_t
lpfc_rdp_res_bbc_desc(struct fc_rdp_bbc_desc *desc, READ_LNK_VAR *stat,
		      struct lpfc_vport *vport)
{
	uint32_t bbCredit;

	desc->tag = cpu_to_be32(RDP_BBC_DESC_TAG);

	bbCredit = vport->fc_sparam.cmn.bbCreditLsb |
			(vport->fc_sparam.cmn.bbCreditMsb << 8);
	desc->bbc_info.port_bbc = cpu_to_be32(bbCredit);
	if (vport->phba->fc_topology != LPFC_TOPOLOGY_LOOP) {
		bbCredit = vport->phba->fc_fabparam.cmn.bbCreditLsb |
			(vport->phba->fc_fabparam.cmn.bbCreditMsb << 8);
		desc->bbc_info.attached_port_bbc = cpu_to_be32(bbCredit);
	} else {
		desc->bbc_info.attached_port_bbc = 0;
	}

	desc->bbc_info.rtt = 0;
	desc->length = cpu_to_be32(sizeof(desc->bbc_info));

	return sizeof(struct fc_rdp_bbc_desc);
}
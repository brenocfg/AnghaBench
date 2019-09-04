#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct qla_tgt_prm {scalar_t__ seg_cnt; int /*<<< orphan*/  sg; TYPE_2__* cmd; } ;
struct TYPE_7__ {int entry_count; int /*<<< orphan*/  dseg_0_address; int /*<<< orphan*/  entry_type; scalar_t__ sys_define; } ;
typedef  TYPE_3__ cont_a64_entry_t ;
struct TYPE_6__ {TYPE_1__* qpair; } ;
struct TYPE_5__ {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUE_A64_TYPE ; 
 int QLA_TGT_DATASEGS_PER_CONT_24XX ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_dma_hi32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_lo32 (int /*<<< orphan*/ ) ; 
 scalar_t__ qlt_get_req_pkt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlt_load_cont_data_segments(struct qla_tgt_prm *prm)
{
	int cnt;
	uint32_t *dword_ptr;

	/* Build continuation packets */
	while (prm->seg_cnt > 0) {
		cont_a64_entry_t *cont_pkt64 =
			(cont_a64_entry_t *)qlt_get_req_pkt(
			   prm->cmd->qpair->req);

		/*
		 * Make sure that from cont_pkt64 none of
		 * 64-bit specific fields used for 32-bit
		 * addressing. Cast to (cont_entry_t *) for
		 * that.
		 */

		memset(cont_pkt64, 0, sizeof(*cont_pkt64));

		cont_pkt64->entry_count = 1;
		cont_pkt64->sys_define = 0;

		cont_pkt64->entry_type = CONTINUE_A64_TYPE;
		dword_ptr = (uint32_t *)&cont_pkt64->dseg_0_address;

		/* Load continuation entry data segments */
		for (cnt = 0;
		    cnt < QLA_TGT_DATASEGS_PER_CONT_24XX && prm->seg_cnt;
		    cnt++, prm->seg_cnt--) {
			*dword_ptr++ =
			    cpu_to_le32(pci_dma_lo32
				(sg_dma_address(prm->sg)));
			*dword_ptr++ = cpu_to_le32(pci_dma_hi32
			    (sg_dma_address(prm->sg)));
			*dword_ptr++ = cpu_to_le32(sg_dma_len(prm->sg));

			prm->sg = sg_next(prm->sg);
		}
	}
}
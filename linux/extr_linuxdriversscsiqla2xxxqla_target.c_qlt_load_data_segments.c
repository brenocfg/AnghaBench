#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_tgt_prm {scalar_t__ seg_cnt; int /*<<< orphan*/  sg; TYPE_1__* cmd; scalar_t__ pkt; } ;
struct TYPE_5__ {scalar_t__* dseg_0_address; void* transfer_length; } ;
struct TYPE_6__ {TYPE_2__ status0; } ;
struct ctio7_to_24xx {int /*<<< orphan*/  dseg_count; TYPE_3__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  bufflen; } ;

/* Variables and functions */
 int QLA_TGT_DATASEGS_PER_CMD_24XX ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_hi32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_lo32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlt_load_cont_data_segments (struct qla_tgt_prm*) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlt_load_data_segments(struct qla_tgt_prm *prm)
{
	int cnt;
	uint32_t *dword_ptr;
	struct ctio7_to_24xx *pkt24 = (struct ctio7_to_24xx *)prm->pkt;

	pkt24->u.status0.transfer_length = cpu_to_le32(prm->cmd->bufflen);

	/* Setup packet address segment pointer */
	dword_ptr = pkt24->u.status0.dseg_0_address;

	/* Set total data segment count */
	if (prm->seg_cnt)
		pkt24->dseg_count = cpu_to_le16(prm->seg_cnt);

	if (prm->seg_cnt == 0) {
		/* No data transfer */
		*dword_ptr++ = 0;
		*dword_ptr = 0;
		return;
	}

	/* If scatter gather */

	/* Load command entry data segments */
	for (cnt = 0;
	    (cnt < QLA_TGT_DATASEGS_PER_CMD_24XX) && prm->seg_cnt;
	    cnt++, prm->seg_cnt--) {
		*dword_ptr++ =
		    cpu_to_le32(pci_dma_lo32(sg_dma_address(prm->sg)));

		*dword_ptr++ = cpu_to_le32(pci_dma_hi32(
			sg_dma_address(prm->sg)));

		*dword_ptr++ = cpu_to_le32(sg_dma_len(prm->sg));

		prm->sg = sg_next(prm->sg);
	}

	qlt_load_cont_data_segments(prm);
}
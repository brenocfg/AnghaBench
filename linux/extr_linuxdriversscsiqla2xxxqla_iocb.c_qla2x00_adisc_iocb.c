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
struct qla_hw_data {int /*<<< orphan*/  async_pd_dma; } ;
struct mbx_entry {void* mb9; void* mb7; void* mb6; void* mb3; void* mb2; void* mb1; void* mb10; void* mb0; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  entry_type; } ;
struct TYPE_7__ {TYPE_2__* vha; TYPE_1__* fcport; } ;
typedef  TYPE_3__ srb_t ;
struct TYPE_6__ {int vp_idx; struct qla_hw_data* hw; } ;
struct TYPE_5__ {int loop_id; } ;

/* Variables and functions */
 int BIT_0 ; 
 scalar_t__ HAS_EXTENDED_IDS (struct qla_hw_data*) ; 
 int LSW (int /*<<< orphan*/ ) ; 
 int MBC_GET_PORT_DATABASE ; 
 int /*<<< orphan*/  MBX_IOCB_TYPE ; 
 int /*<<< orphan*/  MSD (int /*<<< orphan*/ ) ; 
 int MSW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TARGET_ID (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void
qla2x00_adisc_iocb(srb_t *sp, struct mbx_entry *mbx)
{
	struct qla_hw_data *ha = sp->vha->hw;

	mbx->entry_type = MBX_IOCB_TYPE;
	SET_TARGET_ID(ha, mbx->loop_id, sp->fcport->loop_id);
	mbx->mb0 = cpu_to_le16(MBC_GET_PORT_DATABASE);
	if (HAS_EXTENDED_IDS(ha)) {
		mbx->mb1 = cpu_to_le16(sp->fcport->loop_id);
		mbx->mb10 = cpu_to_le16(BIT_0);
	} else {
		mbx->mb1 = cpu_to_le16((sp->fcport->loop_id << 8) | BIT_0);
	}
	mbx->mb2 = cpu_to_le16(MSW(ha->async_pd_dma));
	mbx->mb3 = cpu_to_le16(LSW(ha->async_pd_dma));
	mbx->mb6 = cpu_to_le16(MSW(MSD(ha->async_pd_dma)));
	mbx->mb7 = cpu_to_le16(LSW(MSD(ha->async_pd_dma)));
	mbx->mb9 = cpu_to_le16(sp->vha->vp_idx);
}
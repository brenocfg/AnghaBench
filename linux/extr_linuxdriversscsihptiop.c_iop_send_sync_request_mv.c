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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ internal_req_phy; struct hpt_iop_request_header* internal_req; } ;
struct TYPE_3__ {TYPE_2__ mv; } ;
struct hptiop_hba {scalar_t__ msg_done; TYPE_1__ u; } ;
struct hpt_iop_request_header {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP_REQUEST_FLAG_SYNC_REQUEST ; 
 scalar_t__ MVIOP_MU_QUEUE_ADDR_HOST_BIT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iop_intr_mv (struct hptiop_hba*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mv_inbound_write (scalar_t__,struct hptiop_hba*) ; 

__attribute__((used)) static int iop_send_sync_request_mv(struct hptiop_hba *hba,
					u32 size_bits, u32 millisec)
{
	struct hpt_iop_request_header *reqhdr = hba->u.mv.internal_req;
	u32 i;

	hba->msg_done = 0;
	reqhdr->flags |= cpu_to_le32(IOP_REQUEST_FLAG_SYNC_REQUEST);
	mv_inbound_write(hba->u.mv.internal_req_phy |
			MVIOP_MU_QUEUE_ADDR_HOST_BIT | size_bits, hba);

	for (i = 0; i < millisec; i++) {
		iop_intr_mv(hba);
		if (hba->msg_done)
			return 0;
		msleep(1);
	}
	return -1;
}
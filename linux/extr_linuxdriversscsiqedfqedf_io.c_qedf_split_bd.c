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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
struct scsi_sge {scalar_t__ sge_len; TYPE_1__ sge_addr; } ;
struct qedf_ioreq {TYPE_2__* bd_tbl; } ;
struct TYPE_4__ {struct scsi_sge* bd_tbl; } ;

/* Variables and functions */
 int QEDF_BD_SPLIT_SZ ; 
 int /*<<< orphan*/  U64_HI (scalar_t__) ; 
 int /*<<< orphan*/  U64_LO (scalar_t__) ; 

__attribute__((used)) static int qedf_split_bd(struct qedf_ioreq *io_req, u64 addr, int sg_len,
	int bd_index)
{
	struct scsi_sge *bd = io_req->bd_tbl->bd_tbl;
	int frag_size, sg_frags;

	sg_frags = 0;
	while (sg_len) {
		if (sg_len > QEDF_BD_SPLIT_SZ)
			frag_size = QEDF_BD_SPLIT_SZ;
		else
			frag_size = sg_len;
		bd[bd_index + sg_frags].sge_addr.lo = U64_LO(addr);
		bd[bd_index + sg_frags].sge_addr.hi = U64_HI(addr);
		bd[bd_index + sg_frags].sge_len = (uint16_t)frag_size;

		addr += (u64)frag_size;
		sg_frags++;
		sg_len -= frag_size;
	}
	return sg_frags;
}
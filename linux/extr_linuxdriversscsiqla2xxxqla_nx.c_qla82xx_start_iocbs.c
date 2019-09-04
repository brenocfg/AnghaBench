#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct req_que {int ring_index; int length; int id; int /*<<< orphan*/  ring_ptr; int /*<<< orphan*/  ring; } ;
struct qla_hw_data {int portnum; scalar_t__ nxdb_wr_ptr; int /*<<< orphan*/  nxdb_rd_ptr; struct req_que** req_q_map; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int RD_REG_DWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRT_REG_DWORD (scalar_t__,int) ; 
 scalar_t__ ql2xdbwr ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,unsigned long,int) ; 
 int /*<<< orphan*/  wmb () ; 

void
qla82xx_start_iocbs(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];
	uint32_t dbval;

	/* Adjust ring index. */
	req->ring_index++;
	if (req->ring_index == req->length) {
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	} else
		req->ring_ptr++;

	dbval = 0x04 | (ha->portnum << 5);

	dbval = dbval | (req->id << 8) | (req->ring_index << 16);
	if (ql2xdbwr)
		qla82xx_wr_32(ha, (unsigned long)ha->nxdb_wr_ptr, dbval);
	else {
		WRT_REG_DWORD(ha->nxdb_wr_ptr, dbval);
		wmb();
		while (RD_REG_DWORD(ha->nxdb_rd_ptr) != dbval) {
			WRT_REG_DWORD(ha->nxdb_wr_ptr, dbval);
			wmb();
		}
	}
}
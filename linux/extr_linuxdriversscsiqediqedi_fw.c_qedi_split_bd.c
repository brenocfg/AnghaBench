#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int lo; int hi; } ;
struct scsi_sge {scalar_t__ sge_len; TYPE_2__ sge_addr; } ;
struct TYPE_5__ {struct scsi_sge* sge_tbl; } ;
struct qedi_cmd {TYPE_4__* conn; TYPE_1__ io_tbl; } ;
struct TYPE_8__ {TYPE_3__* qedi; } ;
struct TYPE_7__ {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int QEDI_BD_SPLIT_SZ ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  QEDI_LOG_IO ; 
 int QEDI_PAGE_SIZE ; 

__attribute__((used)) static int qedi_split_bd(struct qedi_cmd *cmd, u64 addr, int sg_len,
			 int bd_index)
{
	struct scsi_sge *bd = cmd->io_tbl.sge_tbl;
	int frag_size, sg_frags;

	sg_frags = 0;

	while (sg_len) {
		if (addr % QEDI_PAGE_SIZE)
			frag_size =
				   (QEDI_PAGE_SIZE - (addr % QEDI_PAGE_SIZE));
		else
			frag_size = (sg_len > QEDI_BD_SPLIT_SZ) ? 0 :
				    (sg_len % QEDI_BD_SPLIT_SZ);

		if (frag_size == 0)
			frag_size = QEDI_BD_SPLIT_SZ;

		bd[bd_index + sg_frags].sge_addr.lo = (addr & 0xffffffff);
		bd[bd_index + sg_frags].sge_addr.hi = (addr >> 32);
		bd[bd_index + sg_frags].sge_len = (u16)frag_size;
		QEDI_INFO(&cmd->conn->qedi->dbg_ctx, QEDI_LOG_IO,
			  "split sge %d: addr=%llx, len=%x",
			  (bd_index + sg_frags), addr, frag_size);

		addr += (u64)frag_size;
		sg_frags++;
		sg_len -= frag_size;
	}
	return sg_frags;
}
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
struct iscsi_bd {scalar_t__ flags; scalar_t__ buffer_length; scalar_t__ buffer_addr_hi; scalar_t__ buffer_addr_lo; } ;
struct TYPE_4__ {int bd_valid; struct iscsi_bd* bd_tbl; } ;
struct bnx2i_cmd {TYPE_2__ io_tbl; TYPE_1__* conn; } ;
struct TYPE_3__ {int /*<<< orphan*/  hba; } ;

/* Variables and functions */
 int bnx2i_map_scsi_sg (int /*<<< orphan*/ ,struct bnx2i_cmd*) ; 

__attribute__((used)) static void bnx2i_iscsi_map_sg_list(struct bnx2i_cmd *cmd)
{
	int bd_count;

	bd_count  = bnx2i_map_scsi_sg(cmd->conn->hba, cmd);
	if (!bd_count) {
		struct iscsi_bd *bd = cmd->io_tbl.bd_tbl;

		bd[0].buffer_addr_lo = bd[0].buffer_addr_hi = 0;
		bd[0].buffer_length = bd[0].flags = 0;
	}
	cmd->io_tbl.bd_valid = bd_count;
}
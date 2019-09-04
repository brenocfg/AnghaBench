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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ScsiReqBlk {TYPE_2__* cmd; } ;
struct AdapterCtlBlk {int dummy; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {scalar_t__ lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  XFERDATAOUT ; 
 int /*<<< orphan*/  clear_fifo (struct AdapterCtlBlk*,char*) ; 
 int /*<<< orphan*/  data_io_transfer (struct AdapterCtlBlk*,struct ScsiReqBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void data_out_phase1(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb,
		u16 *pscsi_status)
{
	dprintkdbg(DBG_0, "data_out_phase1: (0x%p) <%02i-%i>\n",
		srb->cmd, srb->cmd->device->id, (u8)srb->cmd->device->lun);
	clear_fifo(acb, "data_out_phase1");
	/* do prepare before transfer when data out phase */
	data_io_transfer(acb, srb, XFERDATAOUT);
}
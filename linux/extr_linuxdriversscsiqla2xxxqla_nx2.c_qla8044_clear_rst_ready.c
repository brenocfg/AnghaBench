#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {TYPE_1__* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_7__ {int portnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA8044_CRB_DRV_STATE_INDEX ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int qla8044_rd_direct (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla8044_wr_direct (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qla8044_clear_rst_ready(scsi_qla_host_t *vha)
{
	uint32_t drv_state;

	drv_state = qla8044_rd_direct(vha, QLA8044_CRB_DRV_STATE_INDEX);

	/*
	 * For ISP8044, drv_active register has 1 bit per function,
	 * shift 1 by func_num to set a bit for the function.
	 * For ISP82xx, drv_active has 4 bits per function
	 */
	drv_state &= ~(1 << vha->hw->portnum);

	ql_dbg(ql_dbg_p3p, vha, 0xb13d,
	    "drv_state: 0x%08x\n", drv_state);
	qla8044_wr_direct(vha, QLA8044_CRB_DRV_STATE_INDEX, drv_state);
}
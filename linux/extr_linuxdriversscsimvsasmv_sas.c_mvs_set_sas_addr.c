#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mvs_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_port_cfg_data ) (struct mvs_info*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_port_cfg_addr ) (struct mvs_info*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* MVS_CHIP_DISP ; 
 int /*<<< orphan*/  stub1 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mvs_info*,int,int /*<<< orphan*/ ) ; 

void mvs_set_sas_addr(struct mvs_info *mvi, int port_id, u32 off_lo,
		      u32 off_hi, u64 sas_addr)
{
	u32 lo = (u32)sas_addr;
	u32 hi = (u32)(sas_addr>>32);

	MVS_CHIP_DISP->write_port_cfg_addr(mvi, port_id, off_lo);
	MVS_CHIP_DISP->write_port_cfg_data(mvi, port_id, lo);
	MVS_CHIP_DISP->write_port_cfg_addr(mvi, port_id, off_hi);
	MVS_CHIP_DISP->write_port_cfg_data(mvi, port_id, hi);
}
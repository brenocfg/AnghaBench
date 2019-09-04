#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  enum dss_io_pad_mode { ____Placeholder_dss_io_pad_mode } dss_io_pad_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DISPC_CONTROL ; 
#define  DSS_IO_PAD_MODE_BYPASS 130 
#define  DSS_IO_PAD_MODE_RESET 129 
#define  DSS_IO_PAD_MODE_RFBI 128 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dispc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_mgr_set_io_pad_mode(enum dss_io_pad_mode mode)
{
	u32 l;
	int gpout0, gpout1;

	switch (mode) {
	case DSS_IO_PAD_MODE_RESET:
		gpout0 = 0;
		gpout1 = 0;
		break;
	case DSS_IO_PAD_MODE_RFBI:
		gpout0 = 1;
		gpout1 = 0;
		break;
	case DSS_IO_PAD_MODE_BYPASS:
		gpout0 = 1;
		gpout1 = 1;
		break;
	default:
		BUG();
		return;
	}

	l = dispc_read_reg(DISPC_CONTROL);
	l = FLD_MOD(l, gpout0, 15, 15);
	l = FLD_MOD(l, gpout1, 16, 16);
	dispc_write_reg(DISPC_CONTROL, l);
}
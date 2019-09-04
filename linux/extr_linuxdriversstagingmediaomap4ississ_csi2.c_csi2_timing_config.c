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
typedef  int u32 ;
struct iss_csi2_timing_cfg {int stop_state_counter; scalar_t__ stop_state_4x; scalar_t__ stop_state_16x; scalar_t__ force_rx_mode; } ;
struct iss_csi2_device {int /*<<< orphan*/  regs1; int /*<<< orphan*/  iss; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_TIMING ; 
 int CSI2_TIMING_FORCE_RX_MODE_IO1 ; 
 int CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK ; 
 int CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT ; 
 int CSI2_TIMING_STOP_STATE_X16_IO1 ; 
 int CSI2_TIMING_STOP_STATE_X4_IO1 ; 
 int iss_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void csi2_timing_config(struct iss_csi2_device *csi2,
			       struct iss_csi2_timing_cfg *timing)
{
	u32 reg;

	reg = iss_reg_read(csi2->iss, csi2->regs1, CSI2_TIMING);

	if (timing->force_rx_mode)
		reg |= CSI2_TIMING_FORCE_RX_MODE_IO1;
	else
		reg &= ~CSI2_TIMING_FORCE_RX_MODE_IO1;

	if (timing->stop_state_16x)
		reg |= CSI2_TIMING_STOP_STATE_X16_IO1;
	else
		reg &= ~CSI2_TIMING_STOP_STATE_X16_IO1;

	if (timing->stop_state_4x)
		reg |= CSI2_TIMING_STOP_STATE_X4_IO1;
	else
		reg &= ~CSI2_TIMING_STOP_STATE_X4_IO1;

	reg &= ~CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK;
	reg |= timing->stop_state_counter <<
	       CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT;

	iss_reg_write(csi2->iss, csi2->regs1, CSI2_TIMING, reg);
}
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
typedef  int /*<<< orphan*/  fw_port_cap32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PORT_CAP32_FC_RX ; 
 int /*<<< orphan*/  FW_PORT_CAP32_FC_TX ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_100G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_100M ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_10G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_1G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_25G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_40G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_100G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_100M ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_10G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_1G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_25G ; 
 int /*<<< orphan*/  FW_PORT_CAP_SPEED_40G ; 
 int FW_PORT_CMD_LSPEED_V (int /*<<< orphan*/ ) ; 
 int FW_PORT_CMD_RXPAUSE_F ; 
 int FW_PORT_CMD_TXPAUSE_F ; 

fw_port_cap32_t lstatus_to_fwcap(u32 lstatus)
{
	fw_port_cap32_t linkattr = 0;

	/* The format of the Link Status in the old
	 * 16-bit Port Information message isn't the same as the
	 * 16-bit Port Capabilities bitfield used everywhere else.
	 */
	if (lstatus & FW_PORT_CMD_RXPAUSE_F)
		linkattr |= FW_PORT_CAP32_FC_RX;
	if (lstatus & FW_PORT_CMD_TXPAUSE_F)
		linkattr |= FW_PORT_CAP32_FC_TX;
	if (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_100M))
		linkattr |= FW_PORT_CAP32_SPEED_100M;
	if (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_1G))
		linkattr |= FW_PORT_CAP32_SPEED_1G;
	if (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_10G))
		linkattr |= FW_PORT_CAP32_SPEED_10G;
	if (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_25G))
		linkattr |= FW_PORT_CAP32_SPEED_25G;
	if (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_40G))
		linkattr |= FW_PORT_CAP32_SPEED_40G;
	if (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_100G))
		linkattr |= FW_PORT_CAP32_SPEED_100G;

	return linkattr;
}
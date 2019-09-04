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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSI_VC_SHORT_PACKET_HEADER (int) ; 
 int /*<<< orphan*/  DSSERR (char*,scalar_t__) ; 
 scalar_t__ FLD_GET (scalar_t__,int,int) ; 
 scalar_t__ MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT ; 
 scalar_t__ MIPI_DSI_RX_DCS_LONG_READ_RESPONSE ; 
 scalar_t__ MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE ; 
 scalar_t__ MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE ; 
 scalar_t__ REG_GET (struct platform_device*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_show_rx_ack_with_err (scalar_t__) ; 
 int /*<<< orphan*/  dsi_vc_flush_long_data (struct platform_device*,int) ; 

__attribute__((used)) static u16 dsi_vc_flush_receive_data(struct platform_device *dsidev,
		int channel)
{
	/* RX_FIFO_NOT_EMPTY */
	while (REG_GET(dsidev, DSI_VC_CTRL(channel), 20, 20)) {
		u32 val;
		u8 dt;
		val = dsi_read_reg(dsidev, DSI_VC_SHORT_PACKET_HEADER(channel));
		DSSERR("\trawval %#08x\n", val);
		dt = FLD_GET(val, 5, 0);
		if (dt == MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT) {
			u16 err = FLD_GET(val, 23, 8);
			dsi_show_rx_ack_with_err(err);
		} else if (dt == MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE) {
			DSSERR("\tDCS short response, 1 byte: %#x\n",
					FLD_GET(val, 23, 8));
		} else if (dt == MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE) {
			DSSERR("\tDCS short response, 2 byte: %#x\n",
					FLD_GET(val, 23, 8));
		} else if (dt == MIPI_DSI_RX_DCS_LONG_READ_RESPONSE) {
			DSSERR("\tDCS long response, len %d\n",
					FLD_GET(val, 23, 8));
			dsi_vc_flush_long_data(dsidev, channel);
		} else {
			DSSERR("\tunknown datatype 0x%02x\n", dt);
		}
	}
	return 0;
}
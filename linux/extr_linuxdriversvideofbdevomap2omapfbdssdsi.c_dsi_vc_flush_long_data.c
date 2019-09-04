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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VC_CTRL (int) ; 
 int /*<<< orphan*/  DSI_VC_SHORT_PACKET_HEADER (int) ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int,int,int) ; 
 scalar_t__ REG_GET (struct platform_device*,int /*<<< orphan*/ ,int,int) ; 
 int dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_vc_flush_long_data(struct platform_device *dsidev, int channel)
{
	while (REG_GET(dsidev, DSI_VC_CTRL(channel), 20, 20)) {
		u32 val;
		val = dsi_read_reg(dsidev, DSI_VC_SHORT_PACKET_HEADER(channel));
		DSSDBG("\t\tb1 %#02x b2 %#02x b3 %#02x b4 %#02x\n",
				(val >> 0) & 0xff,
				(val >> 8) & 0xff,
				(val >> 16) & 0xff,
				(val >> 24) & 0xff);
	}
}
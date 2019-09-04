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
typedef  int u8 ;
struct platform_device {int dummy; } ;
typedef  enum dss_dsi_content_type { ____Placeholder_dss_dsi_content_type } dss_dsi_content_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DSS_DSI_CONTENT_DCS ; 
 int DSS_DSI_CONTENT_GENERIC ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_LONG_WRITE ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_SHORT_WRITE ; 
 int /*<<< orphan*/  MIPI_DSI_DCS_SHORT_WRITE_PARAM ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_LONG_WRITE ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM ; 
 int /*<<< orphan*/  MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM ; 
 int dsi_vc_send_long (struct platform_device*,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int dsi_vc_send_short (struct platform_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_vc_write_nosync_common(struct platform_device *dsidev,
		int channel, u8 *data, int len, enum dss_dsi_content_type type)
{
	int r;

	if (len == 0) {
		BUG_ON(type == DSS_DSI_CONTENT_DCS);
		r = dsi_vc_send_short(dsidev, channel,
				MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM, 0, 0);
	} else if (len == 1) {
		r = dsi_vc_send_short(dsidev, channel,
				type == DSS_DSI_CONTENT_GENERIC ?
				MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM :
				MIPI_DSI_DCS_SHORT_WRITE, data[0], 0);
	} else if (len == 2) {
		r = dsi_vc_send_short(dsidev, channel,
				type == DSS_DSI_CONTENT_GENERIC ?
				MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM :
				MIPI_DSI_DCS_SHORT_WRITE_PARAM,
				data[0] | (data[1] << 8), 0);
	} else {
		r = dsi_vc_send_long(dsidev, channel,
				type == DSS_DSI_CONTENT_GENERIC ?
				MIPI_DSI_GENERIC_LONG_WRITE :
				MIPI_DSI_DCS_LONG_WRITE, data, len, 0);
	}

	return r;
}
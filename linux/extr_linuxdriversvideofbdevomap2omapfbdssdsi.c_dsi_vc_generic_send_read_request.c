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
typedef  int u16 ;
struct platform_device {int dummy; } ;
struct dsi_data {scalar_t__ debug_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int) ; 
 int /*<<< orphan*/  DSSERR (char*,int,int) ; 
 int EINVAL ; 
 int MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM ; 
 int MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM ; 
 int MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int dsi_vc_send_short (struct platform_device*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi_vc_generic_send_read_request(struct platform_device *dsidev,
		int channel, u8 *reqdata, int reqlen)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);
	u16 data;
	u8 data_type;
	int r;

	if (dsi->debug_read)
		DSSDBG("dsi_vc_generic_send_read_request(ch %d, reqlen %d)\n",
			channel, reqlen);

	if (reqlen == 0) {
		data_type = MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM;
		data = 0;
	} else if (reqlen == 1) {
		data_type = MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM;
		data = reqdata[0];
	} else if (reqlen == 2) {
		data_type = MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM;
		data = reqdata[0] | (reqdata[1] << 8);
	} else {
		BUG();
		return -EINVAL;
	}

	r = dsi_vc_send_short(dsidev, channel, data_type, data, 0);
	if (r) {
		DSSERR("dsi_vc_generic_send_read_request(ch %d, reqlen %d)"
			" failed\n", channel, reqlen);
		return r;
	}

	return 0;
}
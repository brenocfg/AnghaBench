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
typedef  int /*<<< orphan*/  u8 ;
struct platform_device {int dummy; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_DSI_CONTENT_GENERIC ; 
 int EIO ; 
 struct platform_device* dsi_get_dsidev_from_dssdev (struct omap_dss_device*) ; 
 int dsi_vc_generic_send_read_request (struct platform_device*,int,int /*<<< orphan*/ *,int) ; 
 int dsi_vc_read_rx_fifo (struct platform_device*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dsi_vc_send_bta_sync (struct omap_dss_device*,int) ; 

__attribute__((used)) static int dsi_vc_generic_read(struct omap_dss_device *dssdev, int channel,
		u8 *reqdata, int reqlen, u8 *buf, int buflen)
{
	struct platform_device *dsidev = dsi_get_dsidev_from_dssdev(dssdev);
	int r;

	r = dsi_vc_generic_send_read_request(dsidev, channel, reqdata, reqlen);
	if (r)
		return r;

	r = dsi_vc_send_bta_sync(dssdev, channel);
	if (r)
		return r;

	r = dsi_vc_read_rx_fifo(dsidev, channel, buf, buflen,
		DSS_DSI_CONTENT_GENERIC);
	if (r < 0)
		return r;

	if (r != buflen) {
		r = -EIO;
		return r;
	}

	return 0;
}
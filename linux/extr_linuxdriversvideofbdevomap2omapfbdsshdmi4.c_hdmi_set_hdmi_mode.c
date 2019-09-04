#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_dss_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hdmi_dvi_mode; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_DVI ; 
 int /*<<< orphan*/  HDMI_HDMI ; 
 TYPE_2__ hdmi ; 

__attribute__((used)) static int hdmi_set_hdmi_mode(struct omap_dss_device *dssdev,
		bool hdmi_mode)
{
	hdmi.cfg.hdmi_dvi_mode = hdmi_mode ? HDMI_HDMI : HDMI_DVI;
	return 0;
}
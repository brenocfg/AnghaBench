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
typedef  int /*<<< orphan*/  u8 ;
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {int core_enabled; } ;

/* Variables and functions */
 TYPE_1__ hdmi ; 
 int /*<<< orphan*/  hdmi_core_disable (struct omap_dss_device*) ; 
 int hdmi_core_enable (struct omap_dss_device*) ; 
 int read_edid (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hdmi_read_edid(struct omap_dss_device *dssdev,
		u8 *edid, int len)
{
	bool need_enable;
	int r;

	need_enable = hdmi.core_enabled == false;

	if (need_enable) {
		r = hdmi_core_enable(dssdev);
		if (r)
			return r;
	}

	r = read_edid(edid, len);

	if (need_enable)
		hdmi_core_disable(dssdev);

	return r;
}
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
struct platform_device {int dummy; } ;
struct omap_dss_device {int /*<<< orphan*/  dev; } ;
typedef  enum omap_dss_output_id { ____Placeholder_omap_dss_output_id } omap_dss_output_id ;

/* Variables and functions */
 int OMAP_DSS_OUTPUT_DSI1 ; 
 int OMAP_DSS_OUTPUT_DSI2 ; 
 struct omap_dss_device* omap_dss_get_output (int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct platform_device *dsi_get_dsidev_from_id(int module)
{
	struct omap_dss_device *out;
	enum omap_dss_output_id	id;

	switch (module) {
	case 0:
		id = OMAP_DSS_OUTPUT_DSI1;
		break;
	case 1:
		id = OMAP_DSS_OUTPUT_DSI2;
		break;
	default:
		return NULL;
	}

	out = omap_dss_get_output(id);

	return out ? to_platform_device(out->dev) : NULL;
}
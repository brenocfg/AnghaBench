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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sdi; } ;
struct omap_dss_device {char* name; int port_num; int /*<<< orphan*/  owner; TYPE_1__ ops; int /*<<< orphan*/  dispc_channel; int /*<<< orphan*/  output_type; int /*<<< orphan*/  id; int /*<<< orphan*/ * dev; } ;
struct TYPE_4__ {struct omap_dss_device output; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_SDI ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_LCD ; 
 int /*<<< orphan*/  OMAP_DSS_OUTPUT_SDI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  omapdss_register_output (struct omap_dss_device*) ; 
 TYPE_2__ sdi ; 
 int /*<<< orphan*/  sdi_ops ; 

__attribute__((used)) static void sdi_init_output(struct platform_device *pdev)
{
	struct omap_dss_device *out = &sdi.output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_SDI;
	out->output_type = OMAP_DISPLAY_TYPE_SDI;
	out->name = "sdi.0";
	out->dispc_channel = OMAP_DSS_CHANNEL_LCD;
	/* We have SDI only on OMAP3, where it's on port 1 */
	out->port_num = 1;
	out->ops.sdi = &sdi_ops;
	out->owner = THIS_MODULE;

	omapdss_register_output(out);
}
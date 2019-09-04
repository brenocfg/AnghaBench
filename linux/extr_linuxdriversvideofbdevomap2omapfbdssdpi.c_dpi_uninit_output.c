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
struct omap_dss_device {int dummy; } ;
struct dpi_data {struct omap_dss_device output; } ;

/* Variables and functions */
 struct dpi_data* dpi_get_data_from_pdev (struct platform_device*) ; 
 int /*<<< orphan*/  omapdss_unregister_output (struct omap_dss_device*) ; 

__attribute__((used)) static void dpi_uninit_output(struct platform_device *pdev)
{
	struct dpi_data *dpi = dpi_get_data_from_pdev(pdev);
	struct omap_dss_device *out = &dpi->output;

	omapdss_unregister_output(out);
}
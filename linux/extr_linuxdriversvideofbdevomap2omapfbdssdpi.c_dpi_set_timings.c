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
struct omap_video_timings {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct dpi_data {int /*<<< orphan*/  lock; struct omap_video_timings timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dpi_set_timings(struct omap_dss_device *dssdev,
		struct omap_video_timings *timings)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);

	DSSDBG("dpi_set_timings\n");

	mutex_lock(&dpi->lock);

	dpi->timings = *timings;

	mutex_unlock(&dpi->lock);
}
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
struct panel_drv_data {scalar_t__ ulps_timeout; int /*<<< orphan*/  ulps_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsicm_queue_ulps_work(struct panel_drv_data *ddata)
{
	if (ddata->ulps_timeout > 0)
		schedule_delayed_work(&ddata->ulps_work,
				msecs_to_jiffies(ddata->ulps_timeout));
}
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
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_save_sources_filtered (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_source_filter ; 

obs_data_array_t *obs_save_sources(void)
{
	return obs_save_sources_filtered(save_source_filter, NULL);
}
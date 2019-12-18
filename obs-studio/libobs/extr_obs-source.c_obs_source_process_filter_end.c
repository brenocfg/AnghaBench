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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_ptr_valid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_source_process_filter_tech_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void obs_source_process_filter_end(obs_source_t *filter, gs_effect_t *effect,
				   uint32_t width, uint32_t height)
{
	if (!obs_ptr_valid(filter, "obs_source_process_filter_end"))
		return;

	obs_source_process_filter_tech_end(filter, effect, width, height,
					   "Draw");
}
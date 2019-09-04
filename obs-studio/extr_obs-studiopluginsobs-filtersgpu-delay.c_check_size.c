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
typedef  scalar_t__ uint32_t ;
struct gpu_delay_filter_data {int target_valid; scalar_t__ cx; scalar_t__ cy; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_filter_get_target (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_source_get_base_height (int /*<<< orphan*/ *) ; 
 scalar_t__ obs_source_get_base_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_textures (struct gpu_delay_filter_data*) ; 

__attribute__((used)) static inline bool check_size(struct gpu_delay_filter_data *f)
{
	obs_source_t *target = obs_filter_get_target(f->context);
	uint32_t cx;
	uint32_t cy;

	f->target_valid = !!target;
	if (!f->target_valid)
		return true;

	cx = obs_source_get_base_width(target);
	cy = obs_source_get_base_height(target);

	f->target_valid = !!cx && !!cy;
	if (!f->target_valid)
		return true;

	if (cx != f->cx || cy != f->cy) {
		f->cx = cx;
		f->cy = cy;
		reset_textures(f);
		return true;
	}

	return false;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {scalar_t__ video_encoder; TYPE_1__ info; void* scaled_height; void* scaled_width; } ;
typedef  TYPE_2__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int OBS_OUTPUT_ENCODED ; 
 int OBS_OUTPUT_VIDEO ; 
 scalar_t__ active (TYPE_2__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_encoder_set_scaled_size (scalar_t__,void*,void*) ; 
 int /*<<< orphan*/  obs_output_get_name (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_2__*,char*) ; 

void obs_output_set_preferred_size(obs_output_t *output, uint32_t width,
				   uint32_t height)
{
	if (!obs_output_valid(output, "obs_output_set_preferred_size"))
		return;
	if ((output->info.flags & OBS_OUTPUT_VIDEO) == 0)
		return;

	if (active(output)) {
		blog(LOG_WARNING,
		     "output '%s': Cannot set the preferred "
		     "resolution while the output is active",
		     obs_output_get_name(output));
		return;
	}

	output->scaled_width = width;
	output->scaled_height = height;

	if (output->info.flags & OBS_OUTPUT_ENCODED) {
		if (output->video_encoder)
			obs_encoder_set_scaled_size(output->video_encoder,
						    width, height);
	}
}
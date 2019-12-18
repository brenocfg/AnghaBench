#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {scalar_t__ scaled_width; int /*<<< orphan*/  video; int /*<<< orphan*/  video_encoder; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_output_t ;

/* Variables and functions */
 int OBS_OUTPUT_ENCODED ; 
 int OBS_OUTPUT_VIDEO ; 
 scalar_t__ obs_encoder_get_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_2__ const*,char*) ; 
 scalar_t__ video_output_get_width (int /*<<< orphan*/ ) ; 

uint32_t obs_output_get_width(const obs_output_t *output)
{
	if (!obs_output_valid(output, "obs_output_get_width"))
		return 0;
	if ((output->info.flags & OBS_OUTPUT_VIDEO) == 0)
		return 0;

	if (output->info.flags & OBS_OUTPUT_ENCODED)
		return obs_encoder_get_width(output->video_encoder);
	else
		return output->scaled_width != 0
			       ? output->scaled_width
			       : video_output_get_width(output->video);
}
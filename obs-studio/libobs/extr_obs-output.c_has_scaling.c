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
struct obs_output {scalar_t__ scaled_width; scalar_t__ scaled_height; int /*<<< orphan*/  video; } ;

/* Variables and functions */
 scalar_t__ video_output_get_height (int /*<<< orphan*/ ) ; 
 scalar_t__ video_output_get_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool has_scaling(const struct obs_output *output)
{
	uint32_t video_width = video_output_get_width(output->video);
	uint32_t video_height = video_output_get_height(output->video);

	return output->scaled_width && output->scaled_height &&
	       (video_width != output->scaled_width ||
		video_height != output->scaled_height);
}
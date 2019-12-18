#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * video_encoder; } ;
typedef  TYPE_1__ obs_output_t ;
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 scalar_t__ obs_output_valid (TYPE_1__ const*,char*) ; 

obs_encoder_t *obs_output_get_video_encoder(const obs_output_t *output)
{
	return obs_output_valid(output, "obs_output_get_video_encoder")
		       ? output->video_encoder
		       : NULL;
}
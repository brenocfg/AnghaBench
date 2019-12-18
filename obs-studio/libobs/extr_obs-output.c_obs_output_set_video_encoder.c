#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ scaled_height; scalar_t__ scaled_width; TYPE_3__* video_encoder; } ;
typedef  TYPE_2__ obs_output_t ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_14__ {TYPE_1__ info; } ;
typedef  TYPE_3__ obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs_encoder_add_output (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  obs_encoder_remove_output (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  obs_encoder_set_scaled_size (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  obs_output_valid (TYPE_2__*,char*) ; 

void obs_output_set_video_encoder(obs_output_t *output, obs_encoder_t *encoder)
{
	if (!obs_output_valid(output, "obs_output_set_video_encoder"))
		return;
	if (encoder && encoder->info.type != OBS_ENCODER_VIDEO) {
		blog(LOG_WARNING, "obs_output_set_video_encoder: "
				  "encoder passed is not a video encoder");
		return;
	}

	if (output->video_encoder == encoder)
		return;

	obs_encoder_remove_output(output->video_encoder, output);
	obs_encoder_add_output(encoder, output);
	output->video_encoder = encoder;

	/* set the preferred resolution on the encoder */
	if (output->scaled_width && output->scaled_height)
		obs_encoder_set_scaled_size(output->video_encoder,
					    output->scaled_width,
					    output->scaled_height);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_t ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {int /*<<< orphan*/ * media; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ OBS_ENCODER_VIDEO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_encoder_get_name (TYPE_2__ const*) ; 
 int /*<<< orphan*/  obs_encoder_valid (TYPE_2__ const*,char*) ; 

video_t *obs_encoder_video(const obs_encoder_t *encoder)
{
	if (!obs_encoder_valid(encoder, "obs_encoder_video"))
		return NULL;
	if (encoder->info.type != OBS_ENCODER_VIDEO) {
		blog(LOG_WARNING,
		     "obs_encoder_set_video: "
		     "encoder '%s' is not a video encoder",
		     obs_encoder_get_name(encoder));
		return NULL;
	}

	return encoder->media;
}
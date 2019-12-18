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
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {int timebase_num; int /*<<< orphan*/  timebase_den; int /*<<< orphan*/ * media; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_encoder_t ;
typedef  int /*<<< orphan*/  audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ OBS_ENCODER_AUDIO ; 
 int /*<<< orphan*/  audio_output_get_sample_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_encoder_get_name (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_encoder_valid (TYPE_2__*,char*) ; 

void obs_encoder_set_audio(obs_encoder_t *encoder, audio_t *audio)
{
	if (!obs_encoder_valid(encoder, "obs_encoder_set_audio"))
		return;
	if (encoder->info.type != OBS_ENCODER_AUDIO) {
		blog(LOG_WARNING,
		     "obs_encoder_set_audio: "
		     "encoder '%s' is not an audio encoder",
		     obs_encoder_get_name(encoder));
		return;
	}
	if (!audio)
		return;

	encoder->media = audio;
	encoder->timebase_num = 1;
	encoder->timebase_den = audio_output_get_sample_rate(audio);
}
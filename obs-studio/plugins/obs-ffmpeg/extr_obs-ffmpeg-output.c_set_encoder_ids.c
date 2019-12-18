#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  audio_encoder_id; int /*<<< orphan*/  audio_encoder; int /*<<< orphan*/  video_encoder_id; int /*<<< orphan*/  video_encoder; } ;
struct ffmpeg_data {TYPE_3__ config; TYPE_2__* output; } ;
struct TYPE_5__ {TYPE_1__* oformat; } ;
struct TYPE_4__ {void* audio_codec; void* video_codec; } ;

/* Variables and functions */
 void* get_codec_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_encoder_ids(struct ffmpeg_data *data)
{
	data->output->oformat->video_codec = get_codec_id(
		data->config.video_encoder, data->config.video_encoder_id);

	data->output->oformat->audio_codec = get_codec_id(
		data->config.audio_encoder, data->config.audio_encoder_id);
}
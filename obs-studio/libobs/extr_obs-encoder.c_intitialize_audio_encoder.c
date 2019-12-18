#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int (* get_frame_size ) (int /*<<< orphan*/ ) ;} ;
struct obs_encoder {int blocksize; int framesize; int framesize_bytes; TYPE_2__ context; TYPE_1__ info; int /*<<< orphan*/  planes; int /*<<< orphan*/  samplerate; } ;
struct audio_convert_info {int /*<<< orphan*/  speakers; int /*<<< orphan*/  format; int /*<<< orphan*/  samples_per_sec; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_audio_info (struct obs_encoder*,struct audio_convert_info*) ; 
 int /*<<< orphan*/  get_audio_planes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_audio_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_audio_buffers (struct obs_encoder*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intitialize_audio_encoder(struct obs_encoder *encoder)
{
	struct audio_convert_info info = {0};
	get_audio_info(encoder, &info);

	encoder->samplerate = info.samples_per_sec;
	encoder->planes = get_audio_planes(info.format, info.speakers);
	encoder->blocksize = get_audio_size(info.format, info.speakers, 1);
	encoder->framesize =
		encoder->info.get_frame_size(encoder->context.data);

	encoder->framesize_bytes = encoder->blocksize * encoder->framesize;
	reset_audio_buffers(encoder);
}
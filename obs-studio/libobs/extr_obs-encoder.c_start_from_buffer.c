#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct obs_encoder {scalar_t__ first_raw_ts; TYPE_1__* audio_input_buffer; } ;
struct circlebuf {int dummy; } ;
struct audio_data {int /*<<< orphan*/ * data; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {size_t size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t MAX_AV_PLANES ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 size_t calc_offset_size (struct obs_encoder*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_back_audio (struct obs_encoder*,struct audio_data*,size_t,size_t) ; 

__attribute__((used)) static void start_from_buffer(struct obs_encoder *encoder, uint64_t v_start_ts)
{
	size_t size = encoder->audio_input_buffer[0].size;
	struct audio_data audio = {0};
	size_t offset_size = 0;

	for (size_t i = 0; i < MAX_AV_PLANES; i++) {
		audio.data[i] = encoder->audio_input_buffer[i].data;
		memset(&encoder->audio_input_buffer[i], 0,
		       sizeof(struct circlebuf));
	}

	if (encoder->first_raw_ts < v_start_ts)
		offset_size = calc_offset_size(encoder, v_start_ts,
					       encoder->first_raw_ts);

	push_back_audio(encoder, &audio, size, offset_size);

	for (size_t i = 0; i < MAX_AV_PLANES; i++)
		bfree(audio.data[i]);
}
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
struct obs_encoder {size_t planes; int /*<<< orphan*/ * audio_input_buffer; } ;
struct audio_data {scalar_t__* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_push_back (int /*<<< orphan*/ *,scalar_t__,size_t) ; 

__attribute__((used)) static inline void push_back_audio(struct obs_encoder *encoder,
				   struct audio_data *data, size_t size,
				   size_t offset_size)
{
	size -= offset_size;

	/* push in to the circular buffer */
	if (size)
		for (size_t i = 0; i < encoder->planes; i++)
			circlebuf_push_back(&encoder->audio_input_buffer[i],
					    data->data[i] + offset_size, size);
}
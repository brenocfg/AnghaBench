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
struct obs_encoder {size_t planes; int /*<<< orphan*/  framesize_bytes; int /*<<< orphan*/ * audio_output_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  bmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_audio_buffers (struct obs_encoder*) ; 

__attribute__((used)) static inline void reset_audio_buffers(struct obs_encoder *encoder)
{
	free_audio_buffers(encoder);

	for (size_t i = 0; i < encoder->planes; i++)
		encoder->audio_output_buffer[i] =
			bmalloc(encoder->framesize_bytes);
}
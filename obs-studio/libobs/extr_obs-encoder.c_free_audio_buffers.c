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
struct obs_encoder {int /*<<< orphan*/ ** audio_output_buffer; int /*<<< orphan*/ * audio_input_buffer; } ;

/* Variables and functions */
 size_t MAX_AV_PLANES ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_audio_buffers(struct obs_encoder *encoder)
{
	for (size_t i = 0; i < MAX_AV_PLANES; i++) {
		circlebuf_free(&encoder->audio_input_buffer[i]);
		bfree(encoder->audio_output_buffer[i]);
		encoder->audio_output_buffer[i] = NULL;
	}
}
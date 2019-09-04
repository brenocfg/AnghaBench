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

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_audio(struct obs_encoder *encoder)
{
	for (size_t i = 0; i < encoder->planes; i++)
		circlebuf_free(&encoder->audio_input_buffer[i]);
}
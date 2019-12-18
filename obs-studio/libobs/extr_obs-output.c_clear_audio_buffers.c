#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ ** audio_buffer; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 size_t MAX_AUDIO_MIXES ; 
 size_t MAX_AV_PLANES ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_audio_buffers(obs_output_t *output)
{
	for (size_t i = 0; i < MAX_AUDIO_MIXES; i++) {
		for (size_t j = 0; j < MAX_AV_PLANES; j++) {
			circlebuf_free(&output->audio_buffer[i][j]);
		}
	}
}
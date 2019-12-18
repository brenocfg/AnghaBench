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
struct obs_output {int /*<<< orphan*/ * audio_encoders; } ;
typedef  int /*<<< orphan*/  encoded_callback_t ;

/* Variables and functions */
 size_t num_audio_mixes (struct obs_output*) ; 
 int /*<<< orphan*/  obs_encoder_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct obs_output*) ; 

__attribute__((used)) static inline void start_audio_encoders(struct obs_output *output,
					encoded_callback_t encoded_callback)
{
	size_t num_mixes = num_audio_mixes(output);

	for (size_t i = 0; i < num_mixes; i++) {
		obs_encoder_start(output->audio_encoders[i], encoded_callback,
				  output);
	}
}
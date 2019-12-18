#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * audio_encoders; } ;
typedef  TYPE_1__ obs_output_t ;
typedef  int /*<<< orphan*/  encoded_callback_t ;

/* Variables and functions */
 size_t num_audio_mixes (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_encoder_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static inline void stop_audio_encoders(obs_output_t *output,
				       encoded_callback_t encoded_callback)
{
	size_t num_mixes = num_audio_mixes(output);

	for (size_t i = 0; i < num_mixes; i++) {
		obs_encoder_stop(output->audio_encoders[i], encoded_callback,
				 output);
	}
}
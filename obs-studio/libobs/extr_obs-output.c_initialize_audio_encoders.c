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
struct TYPE_3__ {int /*<<< orphan*/ * audio_encoders; } ;
typedef  TYPE_1__ obs_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_encoder_initialize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool initialize_audio_encoders(obs_output_t *output,
					     size_t num_mixes)
{
	for (size_t i = 0; i < num_mixes; i++) {
		if (!obs_encoder_initialize(output->audio_encoders[i])) {
			return false;
		}
	}

	return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* encoded_packet ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct obs_output {int /*<<< orphan*/  interleaved_mutex; TYPE_3__ context; TYPE_2__ info; } ;
struct TYPE_4__ {size_t num; struct obs_output** array; } ;
struct obs_encoder {int initialized; int /*<<< orphan*/  callbacks_mutex; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  outputs_mutex; TYPE_1__ outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_force_stop (struct obs_output*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_connection (struct obs_encoder*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void full_stop(struct obs_encoder *encoder)
{
	if (encoder) {
		pthread_mutex_lock(&encoder->outputs_mutex);
		for (size_t i = 0; i < encoder->outputs.num; i++) {
			struct obs_output *output = encoder->outputs.array[i];
			obs_output_force_stop(output);

			pthread_mutex_lock(&output->interleaved_mutex);
			output->info.encoded_packet(output->context.data, NULL);
			pthread_mutex_unlock(&output->interleaved_mutex);
		}
		pthread_mutex_unlock(&encoder->outputs_mutex);

		pthread_mutex_lock(&encoder->callbacks_mutex);
		da_free(encoder->callbacks);
		pthread_mutex_unlock(&encoder->callbacks_mutex);

		remove_connection(encoder, false);
		encoder->initialized = false;
	}
}
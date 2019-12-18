#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ num; } ;
struct TYPE_7__ {int initialized; int /*<<< orphan*/  init_mutex; scalar_t__ destroy_on_stop; int /*<<< orphan*/  callbacks_mutex; TYPE_6__ callbacks; } ;
typedef  TYPE_1__ obs_encoder_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  da_erase (TYPE_6__,size_t) ; 
 size_t get_callback_idx (TYPE_1__*,void (*) (void*,struct encoder_packet*),void*) ; 
 int /*<<< orphan*/  obs_encoder_actually_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_connection (TYPE_1__*,int) ; 

__attribute__((used)) static inline bool obs_encoder_stop_internal(
	obs_encoder_t *encoder,
	void (*new_packet)(void *param, struct encoder_packet *packet),
	void *param)
{
	bool last = false;
	size_t idx;

	pthread_mutex_lock(&encoder->callbacks_mutex);

	idx = get_callback_idx(encoder, new_packet, param);
	if (idx != DARRAY_INVALID) {
		da_erase(encoder->callbacks, idx);
		last = (encoder->callbacks.num == 0);
	}

	pthread_mutex_unlock(&encoder->callbacks_mutex);

	if (last) {
		remove_connection(encoder, true);
		encoder->initialized = false;

		if (encoder->destroy_on_stop) {
			pthread_mutex_unlock(&encoder->init_mutex);
			obs_encoder_actually_destroy(encoder);
			return true;
		}
	}

	return false;
}
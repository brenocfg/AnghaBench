#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct encoder_callback {int member_0; void (* member_1 ) (void*,struct encoder_packet*) ;void* member_2; } ;
struct TYPE_9__ {scalar_t__ num; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {scalar_t__ cur_pts; int /*<<< orphan*/  pause; int /*<<< orphan*/  paused; int /*<<< orphan*/  callbacks_mutex; TYPE_5__ callbacks; TYPE_1__ context; } ;
typedef  TYPE_2__ obs_encoder_t ;

/* Variables and functions */
 size_t DARRAY_INVALID ; 
 int /*<<< orphan*/  add_connection (TYPE_2__*) ; 
 int /*<<< orphan*/  da_push_back (TYPE_5__,struct encoder_callback*) ; 
 size_t get_callback_idx (TYPE_2__*,void (*) (void*,struct encoder_packet*),void*) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pause_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void obs_encoder_start_internal(
	obs_encoder_t *encoder,
	void (*new_packet)(void *param, struct encoder_packet *packet),
	void *param)
{
	struct encoder_callback cb = {false, new_packet, param};
	bool first = false;

	if (!encoder->context.data)
		return;

	pthread_mutex_lock(&encoder->callbacks_mutex);

	first = (encoder->callbacks.num == 0);

	size_t idx = get_callback_idx(encoder, new_packet, param);
	if (idx == DARRAY_INVALID)
		da_push_back(encoder->callbacks, &cb);

	pthread_mutex_unlock(&encoder->callbacks_mutex);

	if (first) {
		os_atomic_set_bool(&encoder->paused, false);
		pause_reset(&encoder->pause);

		encoder->cur_pts = 0;
		add_connection(encoder);
	}
}
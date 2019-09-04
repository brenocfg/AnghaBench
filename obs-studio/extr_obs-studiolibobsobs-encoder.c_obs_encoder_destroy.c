#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num; } ;
struct TYPE_6__ {int destroy_on_stop; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  callbacks_mutex; TYPE_1__ callbacks; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_context_data_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_encoder_actually_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_encoder_destroy(obs_encoder_t *encoder)
{
	if (encoder) {
		bool destroy;

		obs_context_data_remove(&encoder->context);

		pthread_mutex_lock(&encoder->init_mutex);
		pthread_mutex_lock(&encoder->callbacks_mutex);
		destroy = encoder->callbacks.num == 0;
		if (!destroy)
			encoder->destroy_on_stop = true;
		pthread_mutex_unlock(&encoder->callbacks_mutex);
		pthread_mutex_unlock(&encoder->init_mutex);

		if (destroy)
			obs_encoder_actually_destroy(encoder);
	}
}
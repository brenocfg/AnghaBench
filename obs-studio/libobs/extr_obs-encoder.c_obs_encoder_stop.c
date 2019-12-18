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
struct TYPE_5__ {int /*<<< orphan*/  init_mutex; } ;
typedef  TYPE_1__ obs_encoder_t ;

/* Variables and functions */
 int obs_encoder_stop_internal (TYPE_1__*,void (*) (void*,struct encoder_packet*),void*) ; 
 int /*<<< orphan*/  obs_encoder_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  obs_ptr_valid (void (*) (void*,struct encoder_packet*),char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void obs_encoder_stop(obs_encoder_t *encoder,
		      void (*new_packet)(void *param,
					 struct encoder_packet *packet),
		      void *param)
{
	bool destroyed;

	if (!obs_encoder_valid(encoder, "obs_encoder_stop"))
		return;
	if (!obs_ptr_valid(new_packet, "obs_encoder_stop"))
		return;

	pthread_mutex_lock(&encoder->init_mutex);
	destroyed = obs_encoder_stop_internal(encoder, new_packet, param);
	if (!destroyed)
		pthread_mutex_unlock(&encoder->init_mutex);
}
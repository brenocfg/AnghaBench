#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct obs_core_data {int valid; int /*<<< orphan*/  private_data; int /*<<< orphan*/  main_view; int /*<<< orphan*/  draw_callbacks_mutex; int /*<<< orphan*/  services_mutex; int /*<<< orphan*/  encoders_mutex; int /*<<< orphan*/  outputs_mutex; int /*<<< orphan*/  displays_mutex; int /*<<< orphan*/  audio_sources_mutex; int /*<<< orphan*/  sources_mutex; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
struct TYPE_2__ {struct obs_core_data data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  obs_data_create () ; 
 int /*<<< orphan*/  obs_view_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutexattr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool obs_init_data(void)
{
	struct obs_core_data *data = &obs->data;
	pthread_mutexattr_t attr;

	assert(data != NULL);

	pthread_mutex_init_value(&obs->data.displays_mutex);
	pthread_mutex_init_value(&obs->data.draw_callbacks_mutex);

	if (pthread_mutexattr_init(&attr) != 0)
		return false;
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
		goto fail;
	if (pthread_mutex_init(&data->sources_mutex, &attr) != 0)
		goto fail;
	if (pthread_mutex_init(&data->audio_sources_mutex, &attr) != 0)
		goto fail;
	if (pthread_mutex_init(&data->displays_mutex, &attr) != 0)
		goto fail;
	if (pthread_mutex_init(&data->outputs_mutex, &attr) != 0)
		goto fail;
	if (pthread_mutex_init(&data->encoders_mutex, &attr) != 0)
		goto fail;
	if (pthread_mutex_init(&data->services_mutex, &attr) != 0)
		goto fail;
	if (pthread_mutex_init(&obs->data.draw_callbacks_mutex, &attr) != 0)
		goto fail;
	if (!obs_view_init(&data->main_view))
		goto fail;

	data->private_data = obs_data_create();
	data->valid = true;

fail:
	pthread_mutexattr_destroy(&attr);
	return data->valid;
}
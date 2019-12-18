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
struct obs_core_data {int valid; int /*<<< orphan*/  private_data; int /*<<< orphan*/  tick_callbacks; int /*<<< orphan*/  draw_callbacks; int /*<<< orphan*/  draw_callbacks_mutex; int /*<<< orphan*/  services_mutex; int /*<<< orphan*/  encoders_mutex; int /*<<< orphan*/  outputs_mutex; int /*<<< orphan*/  displays_mutex; int /*<<< orphan*/  audio_sources_mutex; int /*<<< orphan*/  sources_mutex; int /*<<< orphan*/  main_view; } ;
struct TYPE_2__ {struct obs_core_data data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_OBS_LINKED_LIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display ; 
 int /*<<< orphan*/  encoder ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_main_view_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service ; 
 int /*<<< orphan*/  source ; 

__attribute__((used)) static void obs_free_data(void)
{
	struct obs_core_data *data = &obs->data;

	data->valid = false;

	obs_main_view_free(&data->main_view);

	blog(LOG_INFO, "Freeing OBS context data");

	FREE_OBS_LINKED_LIST(source);
	FREE_OBS_LINKED_LIST(output);
	FREE_OBS_LINKED_LIST(encoder);
	FREE_OBS_LINKED_LIST(display);
	FREE_OBS_LINKED_LIST(service);

	pthread_mutex_destroy(&data->sources_mutex);
	pthread_mutex_destroy(&data->audio_sources_mutex);
	pthread_mutex_destroy(&data->displays_mutex);
	pthread_mutex_destroy(&data->outputs_mutex);
	pthread_mutex_destroy(&data->encoders_mutex);
	pthread_mutex_destroy(&data->services_mutex);
	pthread_mutex_destroy(&data->draw_callbacks_mutex);
	da_free(data->draw_callbacks);
	da_free(data->tick_callbacks);
	obs_data_release(data->private_data);
}
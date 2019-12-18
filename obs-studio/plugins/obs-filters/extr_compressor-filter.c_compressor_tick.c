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
typedef  int uint64_t ;
struct compressor_data {int sidechain_check_time; int /*<<< orphan*/  sidechain_update_mutex; int /*<<< orphan*/ * weak_sidechain; scalar_t__ sidechain_name; } ;
typedef  int /*<<< orphan*/  obs_weak_source_t ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (float) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* bstrdup (scalar_t__) ; 
 int /*<<< orphan*/ * obs_get_source_by_name (char*) ; 
 int /*<<< orphan*/  obs_source_add_audio_capture_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct compressor_data*) ; 
 int /*<<< orphan*/ * obs_source_get_weak_source (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_weak_source_release (int /*<<< orphan*/ *) ; 
 int os_gettime_ns () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sidechain_capture ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void compressor_tick(void *data, float seconds)
{
	struct compressor_data *cd = data;
	char *new_name = NULL;

	pthread_mutex_lock(&cd->sidechain_update_mutex);

	if (cd->sidechain_name && !cd->weak_sidechain) {
		uint64_t t = os_gettime_ns();

		if (t - cd->sidechain_check_time > 3000000000) {
			new_name = bstrdup(cd->sidechain_name);
			cd->sidechain_check_time = t;
		}
	}

	pthread_mutex_unlock(&cd->sidechain_update_mutex);

	if (new_name) {
		obs_source_t *sidechain =
			new_name && *new_name ? obs_get_source_by_name(new_name)
					      : NULL;
		obs_weak_source_t *weak_sidechain =
			sidechain ? obs_source_get_weak_source(sidechain)
				  : NULL;

		pthread_mutex_lock(&cd->sidechain_update_mutex);

		if (cd->sidechain_name &&
		    strcmp(cd->sidechain_name, new_name) == 0) {
			cd->weak_sidechain = weak_sidechain;
			weak_sidechain = NULL;
		}

		pthread_mutex_unlock(&cd->sidechain_update_mutex);

		if (sidechain) {
			obs_source_add_audio_capture_callback(
				sidechain, sidechain_capture, cd);

			obs_weak_source_release(weak_sidechain);
			obs_source_release(sidechain);
		}

		bfree(new_name);
	}

	UNUSED_PARAMETER(seconds);
}
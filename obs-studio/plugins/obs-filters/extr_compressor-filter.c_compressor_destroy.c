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
struct compressor_data {struct compressor_data* envelope_buf; struct compressor_data* sidechain_name; int /*<<< orphan*/  sidechain_update_mutex; int /*<<< orphan*/  sidechain_mutex; struct compressor_data** sidechain_buf; int /*<<< orphan*/ * sidechain_data; scalar_t__ weak_sidechain; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 size_t MAX_AUDIO_CHANNELS ; 
 int /*<<< orphan*/  bfree (struct compressor_data*) ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_sidechain (struct compressor_data*) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_remove_audio_capture_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct compressor_data*) ; 
 int /*<<< orphan*/  obs_weak_source_release (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sidechain_capture ; 

__attribute__((used)) static void compressor_destroy(void *data)
{
	struct compressor_data *cd = data;

	if (cd->weak_sidechain) {
		obs_source_t *sidechain = get_sidechain(cd);
		if (sidechain) {
			obs_source_remove_audio_capture_callback(
				sidechain, sidechain_capture, cd);
			obs_source_release(sidechain);
		}

		obs_weak_source_release(cd->weak_sidechain);
	}

	for (size_t i = 0; i < MAX_AUDIO_CHANNELS; i++) {
		circlebuf_free(&cd->sidechain_data[i]);
		bfree(cd->sidechain_buf[i]);
	}
	pthread_mutex_destroy(&cd->sidechain_mutex);
	pthread_mutex_destroy(&cd->sidechain_update_mutex);

	bfree(cd->sidechain_name);
	bfree(cd->envelope_buf);
	bfree(cd);
}
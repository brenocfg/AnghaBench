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
typedef  scalar_t__ uint32_t ;
struct obs_audio_data {scalar_t__ frames; scalar_t__ data; } ;
struct compressor_data {int /*<<< orphan*/  sidechain_update_mutex; int /*<<< orphan*/ * weak_sidechain; } ;
typedef  int /*<<< orphan*/  obs_weak_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  analyze_envelope (struct compressor_data*,float**,scalar_t__ const) ; 
 int /*<<< orphan*/  analyze_sidechain (struct compressor_data*,scalar_t__ const) ; 
 int /*<<< orphan*/  process_compression (struct compressor_data*,float**,scalar_t__ const) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct obs_audio_data *
compressor_filter_audio(void *data, struct obs_audio_data *audio)
{
	struct compressor_data *cd = data;

	const uint32_t num_samples = audio->frames;
	if (num_samples == 0)
		return audio;

	float **samples = (float **)audio->data;

	pthread_mutex_lock(&cd->sidechain_update_mutex);
	obs_weak_source_t *weak_sidechain = cd->weak_sidechain;
	pthread_mutex_unlock(&cd->sidechain_update_mutex);

	if (weak_sidechain)
		analyze_sidechain(cd, num_samples);
	else
		analyze_envelope(cd, samples, num_samples);

	process_compression(cd, samples, num_samples);
	return audio;
}
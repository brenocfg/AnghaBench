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
struct audio_output_info {int /*<<< orphan*/  format; int /*<<< orphan*/  input_param; int /*<<< orphan*/  input_callback; int /*<<< orphan*/  speakers; } ;
struct audio_output {int channels; int planes; int block_size; int initialized; int /*<<< orphan*/  thread; int /*<<< orphan*/  stop_event; int /*<<< orphan*/  input_mutex; int /*<<< orphan*/  input_param; int /*<<< orphan*/  input_cb; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
typedef  struct audio_output audio_t ;

/* Variables and functions */
 int AUDIO_OUTPUT_FAIL ; 
 int AUDIO_OUTPUT_INVALIDPARAM ; 
 int AUDIO_OUTPUT_SUCCESS ; 
 int /*<<< orphan*/  OS_EVENT_TYPE_MANUAL ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  audio_output_close (struct audio_output*) ; 
 int /*<<< orphan*/  audio_thread ; 
 struct audio_output* bzalloc (int) ; 
 int get_audio_bytes_per_channel (int /*<<< orphan*/ ) ; 
 int get_audio_channels (int /*<<< orphan*/ ) ; 
 int is_audio_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct audio_output_info*,int) ; 
 scalar_t__ os_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct audio_output*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_audio_params (struct audio_output_info*) ; 

int audio_output_open(audio_t **audio, struct audio_output_info *info)
{
	struct audio_output *out;
	pthread_mutexattr_t attr;
	bool planar = is_audio_planar(info->format);

	if (!valid_audio_params(info))
		return AUDIO_OUTPUT_INVALIDPARAM;

	out = bzalloc(sizeof(struct audio_output));
	if (!out)
		goto fail;

	memcpy(&out->info, info, sizeof(struct audio_output_info));
	out->channels = get_audio_channels(info->speakers);
	out->planes = planar ? out->channels : 1;
	out->input_cb = info->input_callback;
	out->input_param = info->input_param;
	out->block_size = (planar ? 1 : out->channels) *
			  get_audio_bytes_per_channel(info->format);

	if (pthread_mutexattr_init(&attr) != 0)
		goto fail;
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
		goto fail;
	if (pthread_mutex_init(&out->input_mutex, &attr) != 0)
		goto fail;
	if (os_event_init(&out->stop_event, OS_EVENT_TYPE_MANUAL) != 0)
		goto fail;
	if (pthread_create(&out->thread, NULL, audio_thread, out) != 0)
		goto fail;

	out->initialized = true;
	*audio = out;
	return AUDIO_OUTPUT_SUCCESS;

fail:
	audio_output_close(out);
	return AUDIO_OUTPUT_FAIL;
}
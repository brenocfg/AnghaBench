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
struct obs_core_audio {float user_volume; int /*<<< orphan*/  audio; void* monitoring_device_id; void* monitoring_device_name; int /*<<< orphan*/  monitoring_mutex; } ;
struct audio_output_info {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_mutexattr_t ;
struct TYPE_2__ {struct obs_core_audio audio; } ;

/* Variables and functions */
 int AUDIO_OUTPUT_INVALIDPARAM ; 
 int AUDIO_OUTPUT_SUCCESS ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_RECURSIVE ; 
 int audio_output_open (int /*<<< orphan*/ *,struct audio_output_info*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 void* bstrdup (char*) ; 
 TYPE_1__* obs ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutexattr_settype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool obs_init_audio(struct audio_output_info *ai)
{
	struct obs_core_audio *audio = &obs->audio;
	int errorcode;

	pthread_mutexattr_t attr;

	pthread_mutex_init_value(&audio->monitoring_mutex);

	if (pthread_mutexattr_init(&attr) != 0)
		return false;
	if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
		return false;
	if (pthread_mutex_init(&audio->monitoring_mutex, &attr) != 0)
		return false;

	audio->user_volume = 1.0f;

	audio->monitoring_device_name = bstrdup("Default");
	audio->monitoring_device_id = bstrdup("default");

	errorcode = audio_output_open(&audio->audio, ai);
	if (errorcode == AUDIO_OUTPUT_SUCCESS)
		return true;
	else if (errorcode == AUDIO_OUTPUT_INVALIDPARAM)
		blog(LOG_ERROR, "Invalid audio parameters specified");
	else
		blog(LOG_ERROR, "Could not open audio output");

	return false;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  num; } ;
struct obs_core_video {int /*<<< orphan*/  gpu_encoder_mutex; int /*<<< orphan*/  gpu_encode_inactive; TYPE_2__ gpu_encoders; int /*<<< orphan*/  video; int /*<<< orphan*/  gpu_encoder_active; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;
struct TYPE_3__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_erase_item (TYPE_2__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_gpu_encoding (struct obs_core_video*) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_event_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_gpu_encoding_thread (struct obs_core_video*) ; 
 int /*<<< orphan*/  video_output_dec_texture_encoders (int /*<<< orphan*/ ) ; 

void stop_gpu_encode(obs_encoder_t *encoder)
{
	struct obs_core_video *video = &obs->video;
	bool call_free = false;

	os_atomic_dec_long(&video->gpu_encoder_active);
	video_output_dec_texture_encoders(video->video);

	pthread_mutex_lock(&video->gpu_encoder_mutex);
	da_erase_item(video->gpu_encoders, &encoder);
	if (!video->gpu_encoders.num)
		call_free = true;
	pthread_mutex_unlock(&video->gpu_encoder_mutex);

	os_event_wait(video->gpu_encode_inactive);

	if (call_free) {
		stop_gpu_encoding_thread(video);

		obs_enter_graphics();
		pthread_mutex_lock(&video->gpu_encoder_mutex);
		free_gpu_encoding(video);
		pthread_mutex_unlock(&video->gpu_encoder_mutex);
		obs_leave_graphics();
	}
}
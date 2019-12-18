#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  format_name; int /*<<< orphan*/  path; int /*<<< orphan*/ * scale_pic; int /*<<< orphan*/  swscale; int /*<<< orphan*/  sem; int /*<<< orphan*/  fmt; int /*<<< orphan*/  a; int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ mp_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_decode_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_kill_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_media_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ ) ; 

void mp_media_free(mp_media_t *media)
{
	if (!media)
		return;

	mp_media_stop(media);
	mp_kill_thread(media);
	mp_decode_free(&media->v);
	mp_decode_free(&media->a);
	avformat_close_input(&media->fmt);
	pthread_mutex_destroy(&media->mutex);
	os_sem_destroy(media->sem);
	sws_freeContext(media->swscale);
	av_freep(&media->scale_pic[0]);
	bfree(media->path);
	bfree(media->format_name);
	memset(media, 0, sizeof(*media));
	pthread_mutex_init_value(&media->mutex);
}
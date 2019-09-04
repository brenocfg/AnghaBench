#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ video_cnt; size_t video_head; int video_buffer_size_current; int /*<<< orphan*/  video_buffer_mutex; TYPE_1__* video_ringbuffer; scalar_t__ first; int /*<<< orphan*/  video_grabber_thread; } ;
typedef  TYPE_2__ priv_t ;
struct TYPE_5__ {long long timestamp; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LOOP ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  video_grabber ; 

__attribute__((used)) static double grab_video_frame(priv_t *priv, char *buffer, int len)
{
    int loop_cnt = 0;

    if (priv->first) {
        pthread_create(&priv->video_grabber_thread, NULL, video_grabber, priv);
        priv->first = 0;
    }

    while (priv->video_cnt == 0) {
        usleep(1000);
        if (loop_cnt++ > MAX_LOOP) return 0;
    }

    pthread_mutex_lock(&priv->video_buffer_mutex);
    long long interval = priv->video_ringbuffer[priv->video_head].timestamp;
    memcpy(buffer, priv->video_ringbuffer[priv->video_head].data, len);
    priv->video_cnt--;
    priv->video_head = (priv->video_head+1)%priv->video_buffer_size_current;
    pthread_mutex_unlock(&priv->video_buffer_mutex);

    return interval == -1 ? MP_NOPTS_VALUE : interval*1e-6;
}
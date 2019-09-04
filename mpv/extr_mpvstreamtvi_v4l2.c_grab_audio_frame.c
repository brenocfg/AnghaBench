#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int blocksize; } ;
struct TYPE_7__ {int audio_insert_null_samples; scalar_t__ dropped_frames_timeshift; scalar_t__ dropped_frames_compensated; scalar_t__ audio_usecs_per_block; int audio_head; int audio_tail; int audio_buffer_size; double audio_secs_per_block; scalar_t__ audio_sent_blocks_total; int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  audio_cnt; TYPE_1__ audio_in; scalar_t__ audio_ringbuffer; int /*<<< orphan*/  audio_null_blocks_inserted; scalar_t__ audio_drop; scalar_t__ first; } ;
typedef  TYPE_2__ priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (TYPE_2__*,char*,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static double grab_audio_frame(priv_t *priv, char *buffer, int len)
{
    MP_DBG(priv, "grab_audio_frame(priv=%p, buffer=%p, len=%d)\n",
        priv, buffer, len);

    // hack: if grab_audio_frame is called first, it means we are used by mplayer
    // => switch to the mode which outputs audio immediately, even if
    // it should be silence
    if (priv->first) priv->audio_insert_null_samples = 1;

    pthread_mutex_lock(&priv->audio_mutex);
    while (priv->audio_insert_null_samples
           && priv->dropped_frames_timeshift - priv->dropped_frames_compensated >= priv->audio_usecs_per_block) {
        // some frames were dropped - drop the corresponding number of audio blocks
        if (priv->audio_drop) {
            priv->audio_drop--;
        } else {
            if (priv->audio_head == priv->audio_tail) break;
            priv->audio_head = (priv->audio_head+1) % priv->audio_buffer_size;
        }
        priv->dropped_frames_compensated += priv->audio_usecs_per_block;
    }

    // compensate for dropped audio frames
    if (priv->audio_drop && (priv->audio_head == priv->audio_tail)) {
        priv->audio_drop--;
        memset(buffer, 0, len);
        goto out;
    }

    if (priv->audio_insert_null_samples && (priv->audio_head == priv->audio_tail)) {
        // return silence to avoid desync and stuttering
        memset(buffer, 0, len);
        priv->audio_null_blocks_inserted++;
        goto out;
    }

    pthread_mutex_unlock(&priv->audio_mutex);
    while (priv->audio_head == priv->audio_tail) {
        // this is mencoder => just wait until some audio is available
        usleep(10000);
    }
    pthread_mutex_lock(&priv->audio_mutex);
    memcpy(buffer, priv->audio_ringbuffer+priv->audio_head*priv->audio_in.blocksize, len);
    priv->audio_head = (priv->audio_head+1) % priv->audio_buffer_size;
    priv->audio_cnt--;
out:
    pthread_mutex_unlock(&priv->audio_mutex);
    priv->audio_sent_blocks_total++;
    return (double)priv->audio_sent_blocks_total*priv->audio_secs_per_block;
}
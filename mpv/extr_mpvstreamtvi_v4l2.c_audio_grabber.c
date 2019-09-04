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
struct TYPE_6__ {int blocksize; } ;
struct TYPE_5__ {long long audio_start_time; int aud_skew_cnt; long long* audio_skew_buffer; long long* audio_skew_delta_buffer; int audio_tail; long long first_frame; int audio_recv_blocks_total; long long audio_usecs_per_block; long long audio_skew_total; int audio_skew; long long audio_skew_delta_total; long long audio_skew_measure_time; double audio_skew_factor; int audio_buffer_size; int audio_head; int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  audio_cnt; int /*<<< orphan*/  audio_drop; int /*<<< orphan*/  skew_mutex; int /*<<< orphan*/  clk_id; TYPE_2__ audio_in; scalar_t__ audio_ringbuffer; int /*<<< orphan*/  shutdown; } ;
typedef  TYPE_1__ priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*) ; 
 scalar_t__ audio_in_read_chunk (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  audio_in_start_capture (TYPE_2__*) ; 
 void* get_curr_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *audio_grabber(void *data)
{
    priv_t *priv = (priv_t*)data;
    int i, audio_skew_ptr = 0;
    long long current_time, prev_skew = 0, prev_skew_uncorr = 0;
    long long start_time_avg, curr_timestamp;

    start_time_avg = priv->audio_start_time = get_curr_timestamp(priv->clk_id);
    audio_in_start_capture(&priv->audio_in);
    for (i = 0; i < priv->aud_skew_cnt; i++)
        priv->audio_skew_buffer[i] = 0;
    for (i = 0; i < priv->aud_skew_cnt; i++)
        priv->audio_skew_delta_buffer[i] = 0;

    for (; !priv->shutdown;)
    {
        if (audio_in_read_chunk(&priv->audio_in, priv->audio_ringbuffer+priv->audio_tail*priv->audio_in.blocksize) < 0)
            continue;
        pthread_mutex_lock(&priv->skew_mutex);
        if (priv->first_frame == 0) {
            // there is no first frame yet (unlikely to happen)
            start_time_avg = priv->audio_start_time = get_curr_timestamp(priv->clk_id);
//            fprintf(stderr, "warning - first frame not yet available!\n");
            pthread_mutex_unlock(&priv->skew_mutex);
            continue;
        }
        pthread_mutex_unlock(&priv->skew_mutex);

        priv->audio_recv_blocks_total++;
        curr_timestamp = get_curr_timestamp(priv->clk_id);
        current_time = curr_timestamp - priv->audio_start_time;

        if (priv->audio_recv_blocks_total < priv->aud_skew_cnt*2) {
            start_time_avg += curr_timestamp - priv->audio_usecs_per_block*priv->audio_recv_blocks_total;
            priv->audio_start_time = start_time_avg/(priv->audio_recv_blocks_total+1);
        }

//        fprintf(stderr, "spb = %f, bs = %d, skew = %f\n", priv->audio_secs_per_block, priv->audio_in.blocksize,
//                (double)(current_time - 1e6*priv->audio_secs_per_block*priv->audio_recv_blocks_total)/1e6);

        // put the current skew into the ring buffer
        priv->audio_skew_total -= priv->audio_skew_buffer[audio_skew_ptr];
        priv->audio_skew_buffer[audio_skew_ptr] = current_time
            - priv->audio_usecs_per_block*priv->audio_recv_blocks_total;
        priv->audio_skew_total += priv->audio_skew_buffer[audio_skew_ptr];

        pthread_mutex_lock(&priv->skew_mutex);

        // skew calculation

        // compute the sliding average of the skews
        if (priv->audio_recv_blocks_total > priv->aud_skew_cnt) {
            priv->audio_skew = priv->audio_skew_total/priv->aud_skew_cnt;
        } else {
            priv->audio_skew = priv->audio_skew_total/priv->audio_recv_blocks_total;
        }

        // put the current skew change (skew-prev_skew) into the ring buffer
        priv->audio_skew_delta_total -= priv->audio_skew_delta_buffer[audio_skew_ptr];
        priv->audio_skew_delta_buffer[audio_skew_ptr] = priv->audio_skew - prev_skew_uncorr;
        priv->audio_skew_delta_total += priv->audio_skew_delta_buffer[audio_skew_ptr];
        prev_skew_uncorr = priv->audio_skew; // remember the _uncorrected_ average value

        audio_skew_ptr = (audio_skew_ptr+1) % priv->aud_skew_cnt; // rotate the buffer pointer

        // sliding average approximates the value in the middle of the interval
        // so interpolate the skew value further to the current time
        priv->audio_skew += priv->audio_skew_delta_total/2;

        // now finally, priv->audio_skew contains fairly good approximation
        // of the current value

        // current skew factor (assuming linearity)
        // used for further interpolation in video_grabber
        // probably overkill but seems to be necessary for
        // stress testing by dropping half of the audio frames ;)
        // especially when using ALSA with large block sizes
        // where audio_skew remains a long while behind
        if ((priv->audio_skew_measure_time != 0) && (current_time - priv->audio_skew_measure_time != 0)) {
            priv->audio_skew_factor = (double)(priv->audio_skew-prev_skew)/(current_time - priv->audio_skew_measure_time);
        } else {
            priv->audio_skew_factor = 0.0;
        }

        priv->audio_skew_measure_time = current_time;
        prev_skew = priv->audio_skew;
        priv->audio_skew += priv->audio_start_time - priv->first_frame;
        pthread_mutex_unlock(&priv->skew_mutex);

//        fprintf(stderr, "audio_skew = %f, delta = %f\n", (double)priv->audio_skew/1e6, (double)priv->audio_skew_delta_total/1e6);

        pthread_mutex_lock(&priv->audio_mutex);
        if ((priv->audio_tail+1) % priv->audio_buffer_size == priv->audio_head) {
            MP_ERR(priv, "\ntoo bad - dropping audio frame !\n");
            priv->audio_drop++;
        } else {
            priv->audio_tail = (priv->audio_tail+1) % priv->audio_buffer_size;
            priv->audio_cnt++;
        }
        pthread_mutex_unlock(&priv->audio_mutex);
    }
    return NULL;
}
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
struct TYPE_6__ {int bytes_per_sample; int samplerate; int channels; int blocksize; } ;
struct TYPE_7__ {int video_buffer_size_max; int audio_buffer_size; int aud_skew_cnt; TYPE_1__ audio_in; } ;
typedef  TYPE_2__ priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,int,int,int) ; 
 int getfps (TYPE_2__*) ; 

__attribute__((used)) static void setup_audio_buffer_sizes(priv_t *priv)
{
    int bytes_per_sample = priv->audio_in.bytes_per_sample;
    int seconds = priv->video_buffer_size_max/getfps(priv);

    if (seconds < 5) seconds = 5;
    if (seconds > 500) seconds = 500;

    // make the audio buffer at least as the video buffer capacity (or 5 seconds) long
    priv->audio_buffer_size = 1 + seconds*priv->audio_in.samplerate
        *priv->audio_in.channels
        *bytes_per_sample/priv->audio_in.blocksize;
    if (priv->audio_buffer_size < 256) priv->audio_buffer_size = 256;

    // make the skew buffer at least 1 second long
    priv->aud_skew_cnt = 1 + 1*priv->audio_in.samplerate
        *priv->audio_in.channels
        *bytes_per_sample/priv->audio_in.blocksize;
    if (priv->aud_skew_cnt < 16) priv->aud_skew_cnt = 16;

    MP_VERBOSE(priv, "Audio capture - buffer %d blocks of %d bytes, skew average from %d meas.\n",
           priv->audio_buffer_size, priv->audio_in.blocksize, priv->aud_skew_cnt);
}
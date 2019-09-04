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
struct mp_audio_buffer {int num_samples; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  copy_planes (struct mp_audio_buffer*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mp_audio_buffer_preallocate_min (struct mp_audio_buffer*,int) ; 

void mp_audio_buffer_duplicate(struct mp_audio_buffer *ab, int samples)
{
    assert(samples >= 0 && samples <= ab->num_samples);
    mp_audio_buffer_preallocate_min(ab, ab->num_samples + samples);
    copy_planes(ab, ab->data, ab->num_samples,
                ab->data, ab->num_samples - samples, samples);
    ab->num_samples += samples;
}
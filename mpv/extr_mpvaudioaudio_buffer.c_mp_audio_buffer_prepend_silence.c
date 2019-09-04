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
struct mp_audio_buffer {int num_planes; int sstride; int /*<<< orphan*/  format; int /*<<< orphan*/ * data; scalar_t__ num_samples; } ;

/* Variables and functions */
 int /*<<< orphan*/  af_fill_silence (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  copy_planes (struct mp_audio_buffer*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mp_audio_buffer_preallocate_min (struct mp_audio_buffer*,scalar_t__) ; 

void mp_audio_buffer_prepend_silence(struct mp_audio_buffer *ab, int samples)
{
    assert(samples >= 0);
    mp_audio_buffer_preallocate_min(ab, ab->num_samples + samples);
    copy_planes(ab, ab->data, samples, ab->data, 0, ab->num_samples);
    ab->num_samples += samples;
    for (int n = 0; n < ab->num_planes; n++)
        af_fill_silence(ab->data[n], samples * ab->sstride, ab->format);
}
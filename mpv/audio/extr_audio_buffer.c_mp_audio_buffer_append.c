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
typedef  int /*<<< orphan*/  uint8_t ;
struct mp_audio_buffer {scalar_t__ num_samples; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_planes (struct mp_audio_buffer*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_audio_buffer_preallocate_min (struct mp_audio_buffer*,scalar_t__) ; 

void mp_audio_buffer_append(struct mp_audio_buffer *ab, void **ptr, int samples)
{
    mp_audio_buffer_preallocate_min(ab, ab->num_samples + samples);
    copy_planes(ab, ab->data, ab->num_samples, (uint8_t **)ptr, 0, samples);
    ab->num_samples += samples;
}
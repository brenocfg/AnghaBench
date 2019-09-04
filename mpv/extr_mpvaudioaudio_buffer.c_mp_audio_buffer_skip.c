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
 int /*<<< orphan*/  copy_planes (struct mp_audio_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void mp_audio_buffer_skip(struct mp_audio_buffer *ab, int samples)
{
    assert(samples >= 0 && samples <= ab->num_samples);
    copy_planes(ab, ab->data, 0, ab->data, samples, ab->num_samples - samples);
    ab->num_samples -= samples;
}
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
struct mp_audio_buffer {int allocated; int num_samples; } ;

/* Variables and functions */

int mp_audio_buffer_get_write_available(struct mp_audio_buffer *ab)
{
    return ab->allocated - ab->num_samples;
}
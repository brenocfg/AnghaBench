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
struct mp_audio_buffer {int num_samples; int /*<<< orphan*/ ** data; } ;

/* Variables and functions */

void mp_audio_buffer_peek(struct mp_audio_buffer *ab, uint8_t ***ptr,
                          int *samples)
{
    *ptr = ab->data;
    *samples = ab->num_samples;
}
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

/* Variables and functions */

__attribute__((used)) static void mix_audio_with_buf(float *p_out, float *p_in, float *buf_in,
		size_t pos, size_t count)
{
	register float *out = p_out;
	register float *buf = buf_in + pos;
	register float *in = p_in + pos;
	register float *end = in + count;

	while (in < end)
		*(out++) += *(in++) * *(buf++);
}
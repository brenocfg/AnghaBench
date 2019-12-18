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
struct loopback_pcm {unsigned int buf_pos; unsigned int pcm_buffer_size; } ;

/* Variables and functions */

__attribute__((used)) static inline void bytepos_finish(struct loopback_pcm *dpcm,
				  unsigned int delta)
{
	dpcm->buf_pos += delta;
	dpcm->buf_pos %= dpcm->pcm_buffer_size;
}
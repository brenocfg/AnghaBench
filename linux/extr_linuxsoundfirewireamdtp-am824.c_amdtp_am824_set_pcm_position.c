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
struct amdtp_stream {struct amdtp_am824* protocol; } ;
struct amdtp_am824 {unsigned int pcm_channels; unsigned int* pcm_positions; } ;

/* Variables and functions */

void amdtp_am824_set_pcm_position(struct amdtp_stream *s, unsigned int index,
				 unsigned int position)
{
	struct amdtp_am824 *p = s->protocol;

	if (index < p->pcm_channels)
		p->pcm_positions[index] = position;
}
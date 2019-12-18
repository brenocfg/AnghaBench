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
struct amdtp_stream {int syt_interval; struct amdtp_dot* protocol; } ;
struct amdtp_dot {int* midi_fifo_used; int midi_fifo_limit; } ;

/* Variables and functions */
 int MIDI_BYTES_PER_SECOND ; 
 int max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool midi_ratelimit_per_packet(struct amdtp_stream *s, unsigned int port)
{
	struct amdtp_dot *p = s->protocol;
	int used;

	used = p->midi_fifo_used[port];
	if (used == 0)
		return true;

	used -= MIDI_BYTES_PER_SECOND * s->syt_interval;
	used = max(used, 0);
	p->midi_fifo_used[port] = used;

	return used < p->midi_fifo_limit;
}
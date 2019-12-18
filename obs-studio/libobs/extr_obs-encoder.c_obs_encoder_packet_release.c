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
struct encoder_packet {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (long*) ; 
 int /*<<< orphan*/  memset (struct encoder_packet*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_atomic_dec_long (long*) ; 

void obs_encoder_packet_release(struct encoder_packet *pkt)
{
	if (!pkt)
		return;

	if (pkt->data) {
		long *p_refs = ((long *)pkt->data) - 1;
		if (os_atomic_dec_long(p_refs) == 0)
			bfree(p_refs);
	}

	memset(pkt, 0, sizeof(struct encoder_packet));
}
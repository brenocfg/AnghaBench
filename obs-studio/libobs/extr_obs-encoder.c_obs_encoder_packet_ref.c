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
 int /*<<< orphan*/  os_atomic_inc_long (long*) ; 

void obs_encoder_packet_ref(struct encoder_packet *dst,
			    struct encoder_packet *src)
{
	if (!src)
		return;

	if (src->data) {
		long *p_refs = ((long *)src->data) - 1;
		os_atomic_inc_long(p_refs);
	}

	*dst = *src;
}
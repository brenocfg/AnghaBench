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
typedef  int u32 ;
struct wil_ring {int swhead; int swtail; int size; } ;

/* Variables and functions */

__attribute__((used)) static inline int wil_ring_used_tx(struct wil_ring *ring)
{
	u32 swhead = ring->swhead;
	u32 swtail = ring->swtail;

	return (ring->size + swhead - swtail) % ring->size;
}
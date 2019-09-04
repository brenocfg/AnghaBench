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
typedef  int u8 ;
struct b43legacy_dmaring {size_t index; } ;

/* Variables and functions */

__attribute__((used)) static inline int txring_to_priority(struct b43legacy_dmaring *ring)
{
	static const u8 idx_to_prio[] =
		{ 3, 2, 1, 0, 4, 5, };

/*FIXME: have only one queue, for now */
return 0;

	return idx_to_prio[ring->index];
}
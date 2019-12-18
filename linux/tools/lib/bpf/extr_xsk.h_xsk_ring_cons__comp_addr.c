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
struct xsk_ring_cons {size_t mask; scalar_t__ ring; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  size_t __u32 ;

/* Variables and functions */

__attribute__((used)) static inline const __u64 *
xsk_ring_cons__comp_addr(const struct xsk_ring_cons *comp, __u32 idx)
{
	const __u64 *addrs = (const __u64 *)comp->ring;

	return &addrs[idx & comp->mask];
}
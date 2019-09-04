#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct brcmf_flowring_ring {size_t hash_id; } ;
struct brcmf_flowring {TYPE_1__* hash; struct brcmf_flowring_ring** rings; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifidx; } ;

/* Variables and functions */

u8 brcmf_flowring_ifidx_get(struct brcmf_flowring *flow, u16 flowid)
{
	struct brcmf_flowring_ring *ring;
	u16 hash_idx;

	ring = flow->rings[flowid];
	hash_idx = ring->hash_id;

	return flow->hash[hash_idx].ifidx;
}
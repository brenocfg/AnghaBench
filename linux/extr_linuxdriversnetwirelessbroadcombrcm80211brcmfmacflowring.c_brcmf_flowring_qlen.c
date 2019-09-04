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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct brcmf_flowring_ring {scalar_t__ status; int /*<<< orphan*/  skblist; } ;
struct brcmf_flowring {struct brcmf_flowring_ring** rings; } ;

/* Variables and functions */
 scalar_t__ RING_OPEN ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 

u32 brcmf_flowring_qlen(struct brcmf_flowring *flow, u16 flowid)
{
	struct brcmf_flowring_ring *ring;

	ring = flow->rings[flowid];
	if (!ring)
		return 0;

	if (ring->status != RING_OPEN)
		return 0;

	return skb_queue_len(&ring->skblist);
}
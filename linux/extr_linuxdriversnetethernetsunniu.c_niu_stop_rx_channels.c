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
struct rx_ring_info {int dummy; } ;
struct niu {int num_rx_rings; struct rx_ring_info* rx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  niu_stop_one_rx_channel (struct niu*,struct rx_ring_info*) ; 

__attribute__((used)) static void niu_stop_rx_channels(struct niu *np)
{
	int i;

	for (i = 0; i < np->num_rx_rings; i++) {
		struct rx_ring_info *rp = &np->rx_rings[i];

		niu_stop_one_rx_channel(np, rp);
	}
}
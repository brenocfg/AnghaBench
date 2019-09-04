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
struct tx_ring_info {int /*<<< orphan*/  tx_channel; } ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  niu_tx_channel_stop (struct niu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_stop_one_tx_channel(struct niu *np, struct tx_ring_info *rp)
{
	(void) niu_tx_channel_stop(np, rp->tx_channel);
}
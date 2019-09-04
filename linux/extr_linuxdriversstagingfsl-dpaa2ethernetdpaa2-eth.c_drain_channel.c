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
typedef  scalar_t__ u32 ;
struct dpaa2_eth_priv {int dummy; } ;
struct dpaa2_eth_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ consume_frames (struct dpaa2_eth_channel*) ; 
 int /*<<< orphan*/  pull_channel (struct dpaa2_eth_channel*) ; 

__attribute__((used)) static u32 drain_channel(struct dpaa2_eth_priv *priv,
			 struct dpaa2_eth_channel *ch)
{
	u32 drained = 0, total = 0;

	do {
		pull_channel(ch);
		drained = consume_frames(ch);
		total += drained;
	} while (drained);

	return total;
}
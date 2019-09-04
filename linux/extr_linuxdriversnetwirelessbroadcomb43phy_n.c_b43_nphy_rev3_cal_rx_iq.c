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
typedef  int /*<<< orphan*/  u8 ;
struct nphy_txgains {int dummy; } ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int b43_nphy_rev3_cal_rx_iq(struct b43_wldev *dev,
			struct nphy_txgains target, u8 type, bool debug)
{
	return -1;
}
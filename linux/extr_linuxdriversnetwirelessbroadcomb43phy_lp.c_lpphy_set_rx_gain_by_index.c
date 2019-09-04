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
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPTAB16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_lptab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_set_rx_gain (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpphy_set_rx_gain_by_index(struct b43_wldev *dev, u16 idx)
{
	u32 gain = b43_lptab_read(dev, B43_LPTAB16(12, idx));
	lpphy_set_rx_gain(dev, gain);
}
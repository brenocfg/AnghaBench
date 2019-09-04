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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int b43_phy_read (struct b43_wldev*,int) ; 

__attribute__((used)) static u16 b43_phy_lcn_get_pa_gain(struct b43_wldev *dev)
{
	return (b43_phy_read(dev, 0x4fb) & 0x7f00) >> 8;
}
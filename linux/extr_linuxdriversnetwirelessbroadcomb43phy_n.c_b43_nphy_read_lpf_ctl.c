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
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 scalar_t__ b43_is_40mhz (struct b43_wldev*) ; 
 int b43_ntab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 b43_nphy_read_lpf_ctl(struct b43_wldev *dev, u16 offset)
{
	if (!offset)
		offset = b43_is_40mhz(dev) ? 0x159 : 0x154;
	return b43_ntab_read(dev, B43_NTAB16(7, offset)) & 0x7;
}
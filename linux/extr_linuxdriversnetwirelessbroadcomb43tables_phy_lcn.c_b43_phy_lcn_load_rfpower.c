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
typedef  int u8 ;
typedef  int u32 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LCNTAB32 (int,int) ; 
 int b43_lcntab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_phy_lcn_load_rfpower(struct b43_wldev *dev)
{
	u32 bbmult, rfgain;
	u8 i;

	for (i = 0; i < 128; i++) {
		bbmult = b43_lcntab_read(dev, B43_LCNTAB32(0x7, 0x140 + i));
		bbmult >>= 20;
		rfgain = b43_lcntab_read(dev, B43_LCNTAB32(0x7, 0xc0 + i));

		/* TODO: calculate value for 0x240 + i table offset
		 * b43_lcntab_write(dev, B43_LCNTAB32(0x7, 0x240 + i), val);
		 */
	}
}
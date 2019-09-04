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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LCNTAB16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B43_LCNTAB32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_lcntab_0x00 ; 
 int /*<<< orphan*/  b43_lcntab_0x01 ; 
 int /*<<< orphan*/  b43_lcntab_0x02 ; 
 int /*<<< orphan*/  b43_lcntab_0x0b ; 
 int /*<<< orphan*/  b43_lcntab_0x0c ; 
 int /*<<< orphan*/  b43_lcntab_0x0d ; 
 int /*<<< orphan*/  b43_lcntab_0x0e ; 
 int /*<<< orphan*/  b43_lcntab_0x0f ; 
 int /*<<< orphan*/  b43_lcntab_0x10 ; 
 int /*<<< orphan*/  b43_lcntab_0x11 ; 
 int /*<<< orphan*/  b43_lcntab_0x12 ; 
 int /*<<< orphan*/  b43_lcntab_0x14 ; 
 int /*<<< orphan*/  b43_lcntab_0x17 ; 
 int /*<<< orphan*/  b43_lcntab_0x18 ; 
 int /*<<< orphan*/  lcntab_upload (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_phy_lcn_upload_static_tables(struct b43_wldev *dev)
{
	lcntab_upload(dev, B43_LCNTAB16(0x02, 0), b43_lcntab_0x02);
	lcntab_upload(dev, B43_LCNTAB16(0x01, 0), b43_lcntab_0x01);
	lcntab_upload(dev, B43_LCNTAB32(0x0b, 0), b43_lcntab_0x0b);
	lcntab_upload(dev, B43_LCNTAB32(0x0c, 0), b43_lcntab_0x0c);
	lcntab_upload(dev, B43_LCNTAB32(0x0d, 0), b43_lcntab_0x0d);
	lcntab_upload(dev, B43_LCNTAB16(0x0e, 0), b43_lcntab_0x0e);
	lcntab_upload(dev, B43_LCNTAB16(0x0f, 0), b43_lcntab_0x0f);
	lcntab_upload(dev, B43_LCNTAB16(0x10, 0), b43_lcntab_0x10);
	lcntab_upload(dev, B43_LCNTAB16(0x11, 0), b43_lcntab_0x11);
	lcntab_upload(dev, B43_LCNTAB32(0x12, 0), b43_lcntab_0x12);
	lcntab_upload(dev, B43_LCNTAB16(0x14, 0), b43_lcntab_0x14);
	lcntab_upload(dev, B43_LCNTAB16(0x17, 0), b43_lcntab_0x17);
	lcntab_upload(dev, B43_LCNTAB16(0x00, 0), b43_lcntab_0x00);
	lcntab_upload(dev, B43_LCNTAB32(0x18, 0), b43_lcntab_0x18);
}
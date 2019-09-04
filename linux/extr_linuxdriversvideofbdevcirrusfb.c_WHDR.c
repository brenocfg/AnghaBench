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
struct cirrusfb_info {scalar_t__ btype; } ;

/* Variables and functions */
 scalar_t__ BT_PICASSO ; 
 unsigned char RGen (struct cirrusfb_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGA_PEL_IW ; 
 int /*<<< orphan*/  VGA_PEL_MSK ; 
 int /*<<< orphan*/  WGen (struct cirrusfb_info const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_laguna (struct cirrusfb_info const*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void WHDR(const struct cirrusfb_info *cinfo, unsigned char val)
{
	unsigned char dummy;

	if (is_laguna(cinfo))
		return;
	if (cinfo->btype == BT_PICASSO) {
		/* Klaus' hint for correct access to HDR on some boards */
		/* first write 0 to pixel mask (3c6) */
		WGen(cinfo, VGA_PEL_MSK, 0x00);
		udelay(200);
		/* next read dummy from pixel address (3c8) */
		dummy = RGen(cinfo, VGA_PEL_IW);
		udelay(200);
	}
	/* now do the usual stuff to access the HDR */

	dummy = RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	dummy = RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	dummy = RGen(cinfo, VGA_PEL_MSK);
	udelay(200);
	dummy = RGen(cinfo, VGA_PEL_MSK);
	udelay(200);

	WGen(cinfo, VGA_PEL_MSK, val);
	udelay(200);

	if (cinfo->btype == BT_PICASSO) {
		/* now first reset HDR access counter */
		dummy = RGen(cinfo, VGA_PEL_IW);
		udelay(200);

		/* and at the end, restore the mask value */
		/* ## is this mask always 0xff? */
		WGen(cinfo, VGA_PEL_MSK, 0xff);
		udelay(200);
	}
}
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
struct cirrusfb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void switch_monitor(struct cirrusfb_info *cinfo, int on)
{
#ifdef CONFIG_ZORRO /* only works on Zorro boards */
	static int IsOn = 0;	/* XXX not ok for multiple boards */

	if (cinfo->btype == BT_PICASSO4)
		return;		/* nothing to switch */
	if (cinfo->btype == BT_ALPINE)
		return;		/* nothing to switch */
	if (cinfo->btype == BT_GD5480)
		return;		/* nothing to switch */
	if (cinfo->btype == BT_PICASSO) {
		if ((on && !IsOn) || (!on && IsOn))
			WSFR(cinfo, 0xff);
		return;
	}
	if (on) {
		switch (cinfo->btype) {
		case BT_SD64:
			WSFR(cinfo, cinfo->SFR | 0x21);
			break;
		case BT_PICCOLO:
			WSFR(cinfo, cinfo->SFR | 0x28);
			break;
		case BT_SPECTRUM:
			WSFR(cinfo, 0x6f);
			break;
		default: /* do nothing */ break;
		}
	} else {
		switch (cinfo->btype) {
		case BT_SD64:
			WSFR(cinfo, cinfo->SFR & 0xde);
			break;
		case BT_PICCOLO:
			WSFR(cinfo, cinfo->SFR & 0xd7);
			break;
		case BT_SPECTRUM:
			WSFR(cinfo, 0x4f);
			break;
		default: /* do nothing */
			break;
		}
	}
#endif /* CONFIG_ZORRO */
}
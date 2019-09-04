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
 int ARRAY_SIZE (int const*) ; 
#define  R2059_C1 130 
#define  R2059_C2 129 
#define  R2059_C3 128 
 int const R2059_RFPLL_MASTER ; 
 int const R2059_RFPLL_MISC_CAL_RESETN ; 
 int const R2059_XTAL_CONFIG2 ; 
 int /*<<< orphan*/  b43_radio_2057_rccal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_2059_init_pre (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_2059_rcal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int const,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int const,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  r2059_upload_inittabs (struct b43_wldev*) ; 

__attribute__((used)) static void b43_radio_2059_init(struct b43_wldev *dev)
{
	static const u16 routing[] = { R2059_C1, R2059_C2, R2059_C3 };
	int i;

	/* Prepare (reset?) radio */
	b43_radio_2059_init_pre(dev);

	r2059_upload_inittabs(dev);

	for (i = 0; i < ARRAY_SIZE(routing); i++)
		b43_radio_set(dev, routing[i] | 0x146, 0x3);

	/* Post init starts below */

	b43_radio_set(dev, R2059_RFPLL_MISC_CAL_RESETN, 0x0078);
	b43_radio_set(dev, R2059_XTAL_CONFIG2, 0x0080);
	msleep(2);
	b43_radio_mask(dev, R2059_RFPLL_MISC_CAL_RESETN, ~0x0078);
	b43_radio_mask(dev, R2059_XTAL_CONFIG2, ~0x0080);

	if (1) { /* FIXME */
		b43_radio_2059_rcal(dev);
		b43_radio_2057_rccal(dev);
	}

	b43_radio_mask(dev, R2059_RFPLL_MASTER, ~0x0008);
}
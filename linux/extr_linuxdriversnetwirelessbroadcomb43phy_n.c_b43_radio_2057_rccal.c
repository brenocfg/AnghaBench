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
typedef  int /*<<< orphan*/  u16 ;
struct b43_phy {int radio_rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R2057_RCCAL_DONE_OSCCAP ; 
 int /*<<< orphan*/  R2057_RCCAL_MASTER ; 
 int /*<<< orphan*/  R2057_RCCAL_START_R1_Q1_P1 ; 
 int /*<<< orphan*/  R2057_RCCAL_TRC0 ; 
 int /*<<< orphan*/  R2057_RCCAL_X1 ; 
 int /*<<< orphan*/  R2057v7_RCCAL_MASTER ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_wait_value (struct b43_wldev*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static u16 b43_radio_2057_rccal(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	bool special = (phy->radio_rev == 3 || phy->radio_rev == 4 ||
			phy->radio_rev == 6);
	u16 tmp;

	/* Setup cal */
	if (special) {
		b43_radio_write(dev, R2057_RCCAL_MASTER, 0x61);
		b43_radio_write(dev, R2057_RCCAL_TRC0, 0xC0);
	} else {
		b43_radio_write(dev, R2057v7_RCCAL_MASTER, 0x61);
		b43_radio_write(dev, R2057_RCCAL_TRC0, 0xE9);
	}
	b43_radio_write(dev, R2057_RCCAL_X1, 0x6E);

	/* Start, wait, stop */
	b43_radio_write(dev, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	if (!b43_radio_wait_value(dev, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000))
		b43dbg(dev->wl, "Radio 0x2057 rccal timeout\n");
	usleep_range(35, 70);
	b43_radio_write(dev, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	usleep_range(70, 140);

	/* Setup cal */
	if (special) {
		b43_radio_write(dev, R2057_RCCAL_MASTER, 0x69);
		b43_radio_write(dev, R2057_RCCAL_TRC0, 0xB0);
	} else {
		b43_radio_write(dev, R2057v7_RCCAL_MASTER, 0x69);
		b43_radio_write(dev, R2057_RCCAL_TRC0, 0xD5);
	}
	b43_radio_write(dev, R2057_RCCAL_X1, 0x6E);

	/* Start, wait, stop */
	usleep_range(35, 70);
	b43_radio_write(dev, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	usleep_range(70, 140);
	if (!b43_radio_wait_value(dev, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000))
		b43dbg(dev->wl, "Radio 0x2057 rccal timeout\n");
	usleep_range(35, 70);
	b43_radio_write(dev, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	usleep_range(70, 140);

	/* Setup cal */
	if (special) {
		b43_radio_write(dev, R2057_RCCAL_MASTER, 0x73);
		b43_radio_write(dev, R2057_RCCAL_X1, 0x28);
		b43_radio_write(dev, R2057_RCCAL_TRC0, 0xB0);
	} else {
		b43_radio_write(dev, R2057v7_RCCAL_MASTER, 0x73);
		b43_radio_write(dev, R2057_RCCAL_X1, 0x6E);
		b43_radio_write(dev, R2057_RCCAL_TRC0, 0x99);
	}

	/* Start, wait, stop */
	usleep_range(35, 70);
	b43_radio_write(dev, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	usleep_range(70, 140);
	if (!b43_radio_wait_value(dev, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000)) {
		b43err(dev->wl, "Radio 0x2057 rcal timeout\n");
		return 0;
	}
	tmp = b43_radio_read(dev, R2057_RCCAL_DONE_OSCCAP);
	usleep_range(35, 70);
	b43_radio_write(dev, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	usleep_range(70, 140);

	if (special)
		b43_radio_mask(dev, R2057_RCCAL_MASTER, ~0x1);
	else
		b43_radio_mask(dev, R2057v7_RCCAL_MASTER, ~0x1);

	return tmp;
}
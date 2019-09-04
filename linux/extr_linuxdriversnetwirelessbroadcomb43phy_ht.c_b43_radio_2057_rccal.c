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
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  R2059_RCCAL_DONE_OSCCAP ; 
 int /*<<< orphan*/  R2059_RCCAL_MASTER ; 
 int /*<<< orphan*/  R2059_RCCAL_START_R1_Q1_P1 ; 
 int /*<<< orphan*/  R2059_RCCAL_TRC0 ; 
 int /*<<< orphan*/  R2059_RCCAL_X1 ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_wait_value (struct b43_wldev*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void b43_radio_2057_rccal(struct b43_wldev *dev)
{
	static const u16 radio_values[3][2] = {
		{ 0x61, 0xE9 }, { 0x69, 0xD5 }, { 0x73, 0x99 },
	};
	int i;

	for (i = 0; i < 3; i++) {
		b43_radio_write(dev, R2059_RCCAL_MASTER, radio_values[i][0]);
		b43_radio_write(dev, R2059_RCCAL_X1, 0x6E);
		b43_radio_write(dev, R2059_RCCAL_TRC0, radio_values[i][1]);

		/* Start */
		b43_radio_write(dev, R2059_RCCAL_START_R1_Q1_P1, 0x55);

		/* Wait */
		if (!b43_radio_wait_value(dev, R2059_RCCAL_DONE_OSCCAP, 2, 2,
					  500, 5000000))
			b43err(dev->wl, "Radio 0x2059 rccal timeout\n");

		/* Stop */
		b43_radio_write(dev, R2059_RCCAL_START_R1_Q1_P1, 0x15);
	}

	b43_radio_mask(dev, R2059_RCCAL_MASTER, ~0x1);
}
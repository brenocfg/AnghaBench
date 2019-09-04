#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_radio_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_radio_2064_channel_setup(struct b43_wldev *dev)
{
	u16 save[2];

	b43_radio_set(dev, 0x09d, 0x4);
	b43_radio_write(dev, 0x09e, 0xf);

	/* Channel specific values in theory, in practice always the same */
	b43_radio_write(dev, 0x02a, 0xb);
	b43_radio_maskset(dev, 0x030, ~0x3, 0xa);
	b43_radio_maskset(dev, 0x091, ~0x3, 0);
	b43_radio_maskset(dev, 0x038, ~0xf, 0x7);
	b43_radio_maskset(dev, 0x030, ~0xc, 0x8);
	b43_radio_maskset(dev, 0x05e, ~0xf, 0x8);
	b43_radio_maskset(dev, 0x05e, ~0xf0, 0x80);
	b43_radio_write(dev, 0x06c, 0x80);

	save[0] = b43_radio_read(dev, 0x044);
	save[1] = b43_radio_read(dev, 0x12b);

	b43_radio_set(dev, 0x044, 0x7);
	b43_radio_set(dev, 0x12b, 0xe);

	/* TODO */

	b43_radio_write(dev, 0x040, 0xfb);

	b43_radio_write(dev, 0x041, 0x9a);
	b43_radio_write(dev, 0x042, 0xa3);
	b43_radio_write(dev, 0x043, 0x0c);

	/* TODO */

	b43_radio_set(dev, 0x044, 0x0c);
	udelay(1);

	b43_radio_write(dev, 0x044, save[0]);
	b43_radio_write(dev, 0x12b, save[1]);

	if (dev->phy.rev == 1) {
		/* brcmsmac uses outdated 0x3 for 0x038 */
		b43_radio_write(dev, 0x038, 0x0);
		b43_radio_write(dev, 0x091, 0x7);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct b43_wldev {TYPE_2__* dev; } ;
struct TYPE_4__ {int chip_id; int bus_type; TYPE_1__* bus_sprom; } ;
struct TYPE_3__ {int boardflags_lo; } ;

/* Variables and functions */
 int B43_BFL_PACTRL ; 
 int /*<<< orphan*/  B43_MACCTL_GPOUTSMSK ; 
 int /*<<< orphan*/  B43_MMIO_GPIO_MASK ; 
 int /*<<< orphan*/  B43_MMIO_MACCTL ; 
 int /*<<< orphan*/  b43_maskset16 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_maskset32 (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b43_gpio_init(struct b43_wldev *dev)
{
#ifdef CONFIG_B43_SSB
	struct ssb_device *gpiodev;
#endif
	u32 mask, set;

	b43_maskset32(dev, B43_MMIO_MACCTL, ~B43_MACCTL_GPOUTSMSK, 0);
	b43_maskset16(dev, B43_MMIO_GPIO_MASK, ~0, 0xF);

	mask = 0x0000001F;
	set = 0x0000000F;
	if (dev->dev->chip_id == 0x4301) {
		mask |= 0x0060;
		set |= 0x0060;
	} else if (dev->dev->chip_id == 0x5354) {
		/* Don't allow overtaking buttons GPIOs */
		set &= 0x2; /* 0x2 is LED GPIO on BCM5354 */
	}

	if (0 /* FIXME: conditional unknown */ ) {
		b43_write16(dev, B43_MMIO_GPIO_MASK,
			    b43_read16(dev, B43_MMIO_GPIO_MASK)
			    | 0x0100);
		/* BT Coexistance Input */
		mask |= 0x0080;
		set |= 0x0080;
		/* BT Coexistance Out */
		mask |= 0x0100;
		set |= 0x0100;
	}
	if (dev->dev->bus_sprom->boardflags_lo & B43_BFL_PACTRL) {
		/* PA is controlled by gpio 9, let ucode handle it */
		b43_write16(dev, B43_MMIO_GPIO_MASK,
			    b43_read16(dev, B43_MMIO_GPIO_MASK)
			    | 0x0200);
		mask |= 0x0200;
		set |= 0x0200;
	}

	switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_chipco_gpio_control(&dev->dev->bdev->bus->drv_cc, mask, set);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		gpiodev = b43_ssb_gpio_dev(dev);
		if (gpiodev)
			ssb_write32(gpiodev, B43_GPIO_CONTROL,
				    (ssb_read32(gpiodev, B43_GPIO_CONTROL)
				    & ~mask) | set);
		break;
#endif
	}

	return 0;
}
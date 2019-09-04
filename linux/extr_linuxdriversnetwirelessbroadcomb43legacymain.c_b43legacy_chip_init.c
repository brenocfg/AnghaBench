#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct b43legacy_phy {int interfmode; scalar_t__ type; int /*<<< orphan*/  txerr_cnt; scalar_t__ gmode; } ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; TYPE_4__* dev; struct b43legacy_phy phy; } ;
struct TYPE_6__ {int revision; } ;
struct TYPE_9__ {TYPE_3__* bus; TYPE_1__ id; } ;
struct TYPE_7__ {int fast_pwrup_delay; } ;
struct TYPE_8__ {TYPE_2__ chipco; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_ANTENNA_DEFAULT ; 
 int B43legacy_INTERFMODE_NONE ; 
 int B43legacy_MACCTL_GMODE ; 
 int B43legacy_MACCTL_IHR_ENABLED ; 
 int B43legacy_MACCTL_INFRA ; 
 int B43legacy_MACCTL_SHM_ENABLED ; 
 int B43legacy_MMIO_DMA0_IRQ_MASK ; 
 int B43legacy_MMIO_DMA1_IRQ_MASK ; 
 int B43legacy_MMIO_DMA2_IRQ_MASK ; 
 int B43legacy_MMIO_DMA3_IRQ_MASK ; 
 int B43legacy_MMIO_DMA4_IRQ_MASK ; 
 int B43legacy_MMIO_DMA5_IRQ_MASK ; 
 int B43legacy_MMIO_GEN_IRQ_REASON ; 
 int B43legacy_MMIO_MACCTL ; 
 int B43legacy_MMIO_POWERUP_DELAY ; 
 scalar_t__ B43legacy_PHYTYPE_B ; 
 int /*<<< orphan*/  B43legacy_PHY_TX_BADNESS_LIMIT ; 
 int /*<<< orphan*/  B43legacy_SHM_SHARED ; 
 int B43legacy_TMSLOW_MACPHYCLKEN ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  SSB_TMSLOW ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_adjust_opmode (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_gpio_cleanup (struct b43legacy_wldev*) ; 
 int b43legacy_gpio_init (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_mgmtframe_txantenna (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int b43legacy_phy_init (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_set_antenna_diversity (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_radio_set_interference_mitigation (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_turn_off (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_turn_on (struct b43legacy_wldev*) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_shm_write16 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43legacy_upload_initvals (struct b43legacy_wldev*) ; 
 int b43legacy_upload_microcode (struct b43legacy_wldev*) ; 
 scalar_t__ b43legacy_using_pio (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacydbg (int /*<<< orphan*/ ,char*) ; 
 int ssb_read32 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_write32 (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b43legacy_chip_init(struct b43legacy_wldev *dev)
{
	struct b43legacy_phy *phy = &dev->phy;
	int err;
	int tmp;
	u32 value32, macctl;
	u16 value16;

	/* Initialize the MAC control */
	macctl = B43legacy_MACCTL_IHR_ENABLED | B43legacy_MACCTL_SHM_ENABLED;
	if (dev->phy.gmode)
		macctl |= B43legacy_MACCTL_GMODE;
	macctl |= B43legacy_MACCTL_INFRA;
	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, macctl);

	err = b43legacy_upload_microcode(dev);
	if (err)
		goto out; /* firmware is released later */

	err = b43legacy_gpio_init(dev);
	if (err)
		goto out; /* firmware is released later */

	err = b43legacy_upload_initvals(dev);
	if (err)
		goto err_gpio_clean;
	b43legacy_radio_turn_on(dev);

	b43legacy_write16(dev, 0x03E6, 0x0000);
	err = b43legacy_phy_init(dev);
	if (err)
		goto err_radio_off;

	/* Select initial Interference Mitigation. */
	tmp = phy->interfmode;
	phy->interfmode = B43legacy_INTERFMODE_NONE;
	b43legacy_radio_set_interference_mitigation(dev, tmp);

	b43legacy_phy_set_antenna_diversity(dev);
	b43legacy_mgmtframe_txantenna(dev, B43legacy_ANTENNA_DEFAULT);

	if (phy->type == B43legacy_PHYTYPE_B) {
		value16 = b43legacy_read16(dev, 0x005E);
		value16 |= 0x0004;
		b43legacy_write16(dev, 0x005E, value16);
	}
	b43legacy_write32(dev, 0x0100, 0x01000000);
	if (dev->dev->id.revision < 5)
		b43legacy_write32(dev, 0x010C, 0x01000000);

	value32 = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	value32 &= ~B43legacy_MACCTL_INFRA;
	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, value32);
	value32 = b43legacy_read32(dev, B43legacy_MMIO_MACCTL);
	value32 |= B43legacy_MACCTL_INFRA;
	b43legacy_write32(dev, B43legacy_MMIO_MACCTL, value32);

	if (b43legacy_using_pio(dev)) {
		b43legacy_write32(dev, 0x0210, 0x00000100);
		b43legacy_write32(dev, 0x0230, 0x00000100);
		b43legacy_write32(dev, 0x0250, 0x00000100);
		b43legacy_write32(dev, 0x0270, 0x00000100);
		b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0034,
				      0x0000);
	}

	/* Probe Response Timeout value */
	/* FIXME: Default to 0, has to be set by ioctl probably... :-/ */
	b43legacy_shm_write16(dev, B43legacy_SHM_SHARED, 0x0074, 0x0000);

	/* Initially set the wireless operation mode. */
	b43legacy_adjust_opmode(dev);

	if (dev->dev->id.revision < 3) {
		b43legacy_write16(dev, 0x060E, 0x0000);
		b43legacy_write16(dev, 0x0610, 0x8000);
		b43legacy_write16(dev, 0x0604, 0x0000);
		b43legacy_write16(dev, 0x0606, 0x0200);
	} else {
		b43legacy_write32(dev, 0x0188, 0x80000000);
		b43legacy_write32(dev, 0x018C, 0x02000000);
	}
	b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_REASON, 0x00004000);
	b43legacy_write32(dev, B43legacy_MMIO_DMA0_IRQ_MASK, 0x0001DC00);
	b43legacy_write32(dev, B43legacy_MMIO_DMA1_IRQ_MASK, 0x0000DC00);
	b43legacy_write32(dev, B43legacy_MMIO_DMA2_IRQ_MASK, 0x0000DC00);
	b43legacy_write32(dev, B43legacy_MMIO_DMA3_IRQ_MASK, 0x0001DC00);
	b43legacy_write32(dev, B43legacy_MMIO_DMA4_IRQ_MASK, 0x0000DC00);
	b43legacy_write32(dev, B43legacy_MMIO_DMA5_IRQ_MASK, 0x0000DC00);

	value32 = ssb_read32(dev->dev, SSB_TMSLOW);
	value32 |= B43legacy_TMSLOW_MACPHYCLKEN;
	ssb_write32(dev->dev, SSB_TMSLOW, value32);

	b43legacy_write16(dev, B43legacy_MMIO_POWERUP_DELAY,
			  dev->dev->bus->chipco.fast_pwrup_delay);

	/* PHY TX errors counter. */
	atomic_set(&phy->txerr_cnt, B43legacy_PHY_TX_BADNESS_LIMIT);

	B43legacy_WARN_ON(err != 0);
	b43legacydbg(dev->wl, "Chip initialized\n");
out:
	return err;

err_radio_off:
	b43legacy_radio_turn_off(dev, 1);
err_gpio_clean:
	b43legacy_gpio_cleanup(dev);
	goto out;
}
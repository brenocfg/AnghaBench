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
struct via82xx {scalar_t__ chip_type; int ac97_secondary; int port; int /*<<< orphan*/ * playback_volume_c; int /*<<< orphan*/ ** playback_volume; struct pci_dev* pci; TYPE_1__* card; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPI_INTR ; 
 scalar_t__ TYPE_VIA686 ; 
 scalar_t__ TYPE_VIA8233A ; 
 int /*<<< orphan*/  VIAREG (struct via82xx*,int /*<<< orphan*/ ) ; 
 unsigned char VIA_ACLINK_C00_READY ; 
 int VIA_ACLINK_CTRL ; 
 unsigned char VIA_ACLINK_CTRL_ENABLE ; 
 unsigned char VIA_ACLINK_CTRL_INIT ; 
 unsigned char VIA_ACLINK_CTRL_RESET ; 
 unsigned char VIA_ACLINK_CTRL_SYNC ; 
 int VIA_ACLINK_STAT ; 
 int VIA_FM_NMI_CTRL ; 
 int VIA_FUNC_ENABLE ; 
 unsigned int VIA_REG_AC97_BUSY ; 
 unsigned int VIA_REG_AC97_CODEC_ID_SECONDARY ; 
 unsigned int VIA_REG_AC97_CODEC_ID_SHIFT ; 
 unsigned int VIA_REG_AC97_READ ; 
 unsigned int VIA_REG_AC97_SECONDARY_VALID ; 
 scalar_t__ VIA_REG_OFS_PLAYBACK_VOLUME_L ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,unsigned char) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 unsigned int snd_via82xx_codec_xread (struct via82xx*) ; 
 int /*<<< orphan*/  snd_via82xx_codec_xwrite (struct via82xx*,unsigned int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_via82xx_chip_init(struct via82xx *chip)
{
	unsigned int val;
	unsigned long end_time;
	unsigned char pval;

#if 0 /* broken on K7M? */
	if (chip->chip_type == TYPE_VIA686)
		/* disable all legacy ports */
		pci_write_config_byte(chip->pci, VIA_FUNC_ENABLE, 0);
#endif
	pci_read_config_byte(chip->pci, VIA_ACLINK_STAT, &pval);
	if (! (pval & VIA_ACLINK_C00_READY)) { /* codec not ready? */
		/* deassert ACLink reset, force SYNC */
		pci_write_config_byte(chip->pci, VIA_ACLINK_CTRL,
				      VIA_ACLINK_CTRL_ENABLE |
				      VIA_ACLINK_CTRL_RESET |
				      VIA_ACLINK_CTRL_SYNC);
		udelay(100);
#if 1 /* FIXME: should we do full reset here for all chip models? */
		pci_write_config_byte(chip->pci, VIA_ACLINK_CTRL, 0x00);
		udelay(100);
#else
		/* deassert ACLink reset, force SYNC (warm AC'97 reset) */
		pci_write_config_byte(chip->pci, VIA_ACLINK_CTRL,
				      VIA_ACLINK_CTRL_RESET|VIA_ACLINK_CTRL_SYNC);
		udelay(2);
#endif
		/* ACLink on, deassert ACLink reset, VSR, SGD data out */
		/* note - FM data out has trouble with non VRA codecs !! */
		pci_write_config_byte(chip->pci, VIA_ACLINK_CTRL, VIA_ACLINK_CTRL_INIT);
		udelay(100);
	}
	
	/* Make sure VRA is enabled, in case we didn't do a
	 * complete codec reset, above */
	pci_read_config_byte(chip->pci, VIA_ACLINK_CTRL, &pval);
	if ((pval & VIA_ACLINK_CTRL_INIT) != VIA_ACLINK_CTRL_INIT) {
		/* ACLink on, deassert ACLink reset, VSR, SGD data out */
		/* note - FM data out has trouble with non VRA codecs !! */
		pci_write_config_byte(chip->pci, VIA_ACLINK_CTRL, VIA_ACLINK_CTRL_INIT);
		udelay(100);
	}

	/* wait until codec ready */
	end_time = jiffies + msecs_to_jiffies(750);
	do {
		pci_read_config_byte(chip->pci, VIA_ACLINK_STAT, &pval);
		if (pval & VIA_ACLINK_C00_READY) /* primary codec ready */
			break;
		schedule_timeout_uninterruptible(1);
	} while (time_before(jiffies, end_time));

	if ((val = snd_via82xx_codec_xread(chip)) & VIA_REG_AC97_BUSY)
		dev_err(chip->card->dev,
			"AC'97 codec is not ready [0x%x]\n", val);

#if 0 /* FIXME: we don't support the second codec yet so skip the detection now.. */
	snd_via82xx_codec_xwrite(chip, VIA_REG_AC97_READ |
				 VIA_REG_AC97_SECONDARY_VALID |
				 (VIA_REG_AC97_CODEC_ID_SECONDARY << VIA_REG_AC97_CODEC_ID_SHIFT));
	end_time = jiffies + msecs_to_jiffies(750);
	snd_via82xx_codec_xwrite(chip, VIA_REG_AC97_READ |
				 VIA_REG_AC97_SECONDARY_VALID |
				 (VIA_REG_AC97_CODEC_ID_SECONDARY << VIA_REG_AC97_CODEC_ID_SHIFT));
	do {
		if ((val = snd_via82xx_codec_xread(chip)) & VIA_REG_AC97_SECONDARY_VALID) {
			chip->ac97_secondary = 1;
			goto __ac97_ok2;
		}
		schedule_timeout_uninterruptible(1);
	} while (time_before(jiffies, end_time));
	/* This is ok, the most of motherboards have only one codec */

      __ac97_ok2:
#endif

	if (chip->chip_type == TYPE_VIA686) {
		/* route FM trap to IRQ, disable FM trap */
		pci_write_config_byte(chip->pci, VIA_FM_NMI_CTRL, 0);
		/* disable all GPI interrupts */
		outl(0, VIAREG(chip, GPI_INTR));
	}

	if (chip->chip_type != TYPE_VIA686) {
		/* Workaround for Award BIOS bug:
		 * DXS channels don't work properly with VRA if MC97 is disabled.
		 */
		struct pci_dev *pci;
		pci = pci_get_device(0x1106, 0x3068, NULL); /* MC97 */
		if (pci) {
			unsigned char data;
			pci_read_config_byte(pci, 0x44, &data);
			pci_write_config_byte(pci, 0x44, data | 0x40);
			pci_dev_put(pci);
		}
	}

	if (chip->chip_type != TYPE_VIA8233A) {
		int i, idx;
		for (idx = 0; idx < 4; idx++) {
			unsigned long port = chip->port + 0x10 * idx;
			for (i = 0; i < 2; i++) {
				chip->playback_volume[idx][i]=chip->playback_volume_c[i];
				outb(chip->playback_volume_c[i],
				     port + VIA_REG_OFS_PLAYBACK_VOLUME_L + i);
			}
		}
	}

	return 0;
}
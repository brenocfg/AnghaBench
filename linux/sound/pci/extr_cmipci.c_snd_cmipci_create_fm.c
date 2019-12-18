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
struct snd_opl3 {int dummy; } ;
struct cmipci {int chip_version; long iobase; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CM_FMSEL_388 ; 
 unsigned int CM_FMSEL_3C8 ; 
 unsigned int CM_FMSEL_3E0 ; 
 unsigned int CM_FMSEL_3E8 ; 
 unsigned int CM_FMSEL_MASK ; 
 unsigned int CM_FM_EN ; 
 long CM_REG_FM_PCI ; 
 int /*<<< orphan*/  CM_REG_LEGACY_CTRL ; 
 int /*<<< orphan*/  CM_REG_MISC_CTRL ; 
 int EIO ; 
 int /*<<< orphan*/  OPL3_HW_OPL3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int snd_cmipci_read (struct cmipci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_set_bit (struct cmipci*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_cmipci_write (struct cmipci*,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_opl3_create (TYPE_1__*,long,long,int /*<<< orphan*/ ,int,struct snd_opl3**) ; 
 int snd_opl3_hwdep_new (struct snd_opl3*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cmipci_create_fm(struct cmipci *cm, long fm_port)
{
	long iosynth;
	unsigned int val;
	struct snd_opl3 *opl3;
	int err;

	if (!fm_port)
		goto disable_fm;

	if (cm->chip_version >= 39) {
		/* first try FM regs in PCI port range */
		iosynth = cm->iobase + CM_REG_FM_PCI;
		err = snd_opl3_create(cm->card, iosynth, iosynth + 2,
				      OPL3_HW_OPL3, 1, &opl3);
	} else {
		err = -EIO;
	}
	if (err < 0) {
		/* then try legacy ports */
		val = snd_cmipci_read(cm, CM_REG_LEGACY_CTRL) & ~CM_FMSEL_MASK;
		iosynth = fm_port;
		switch (iosynth) {
		case 0x3E8: val |= CM_FMSEL_3E8; break;
		case 0x3E0: val |= CM_FMSEL_3E0; break;
		case 0x3C8: val |= CM_FMSEL_3C8; break;
		case 0x388: val |= CM_FMSEL_388; break;
		default:
			goto disable_fm;
		}
		snd_cmipci_write(cm, CM_REG_LEGACY_CTRL, val);
		/* enable FM */
		snd_cmipci_set_bit(cm, CM_REG_MISC_CTRL, CM_FM_EN);

		if (snd_opl3_create(cm->card, iosynth, iosynth + 2,
				    OPL3_HW_OPL3, 0, &opl3) < 0) {
			dev_err(cm->card->dev,
				"no OPL device at %#lx, skipping...\n",
				iosynth);
			goto disable_fm;
		}
	}
	if ((err = snd_opl3_hwdep_new(opl3, 0, 1, NULL)) < 0) {
		dev_err(cm->card->dev, "cannot create OPL3 hwdep\n");
		return err;
	}
	return 0;

 disable_fm:
	snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_FMSEL_MASK);
	snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_FM_EN);
	return 0;
}
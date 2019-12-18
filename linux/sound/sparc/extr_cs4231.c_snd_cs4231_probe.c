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
struct snd_cs4231 {int* image; int /*<<< orphan*/  lock; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231U (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 size_t CS4231_ALT_FEATURE_1 ; 
 size_t CS4231_ALT_FEATURE_2 ; 
 size_t CS4231_IFACE_CTRL ; 
 int CS4231_INIT ; 
 size_t CS4231_MISC_INFO ; 
 int CS4231_MODE2 ; 
 int CS4231_SINGLE_DMA ; 
 size_t CS4231_VERSION ; 
 int ENODEV ; 
 int /*<<< orphan*/  REGSEL ; 
 int /*<<< orphan*/  STATUS ; 
 int __cs4231_readb (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cs4231_writeb (struct snd_cs4231*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_cs4231_in (struct snd_cs4231*,size_t) ; 
 int /*<<< orphan*/  snd_cs4231_mce_down (struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_cs4231_mce_up (struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_cs4231_out (struct snd_cs4231*,int,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_cs4231_probe(struct snd_cs4231 *chip)
{
	unsigned long flags;
	int i;
	int id = 0;
	int vers = 0;
	unsigned char *ptr;

	for (i = 0; i < 50; i++) {
		mb();
		if (__cs4231_readb(chip, CS4231U(chip, REGSEL)) & CS4231_INIT)
			msleep(2);
		else {
			spin_lock_irqsave(&chip->lock, flags);
			snd_cs4231_out(chip, CS4231_MISC_INFO, CS4231_MODE2);
			id = snd_cs4231_in(chip, CS4231_MISC_INFO) & 0x0f;
			vers = snd_cs4231_in(chip, CS4231_VERSION);
			spin_unlock_irqrestore(&chip->lock, flags);
			if (id == 0x0a)
				break;	/* this is valid value */
		}
	}
	snd_printdd("cs4231: port = %p, id = 0x%x\n", chip->port, id);
	if (id != 0x0a)
		return -ENODEV;	/* no valid device found */

	spin_lock_irqsave(&chip->lock, flags);

	/* clear any pendings IRQ */
	__cs4231_readb(chip, CS4231U(chip, STATUS));
	__cs4231_writeb(chip, 0, CS4231U(chip, STATUS));
	mb();

	spin_unlock_irqrestore(&chip->lock, flags);

	chip->image[CS4231_MISC_INFO] = CS4231_MODE2;
	chip->image[CS4231_IFACE_CTRL] =
		chip->image[CS4231_IFACE_CTRL] & ~CS4231_SINGLE_DMA;
	chip->image[CS4231_ALT_FEATURE_1] = 0x80;
	chip->image[CS4231_ALT_FEATURE_2] = 0x01;
	if (vers & 0x20)
		chip->image[CS4231_ALT_FEATURE_2] |= 0x02;

	ptr = (unsigned char *) &chip->image;

	snd_cs4231_mce_down(chip);

	spin_lock_irqsave(&chip->lock, flags);

	for (i = 0; i < 32; i++)	/* ok.. fill all CS4231 registers */
		snd_cs4231_out(chip, i, *ptr++);

	spin_unlock_irqrestore(&chip->lock, flags);

	snd_cs4231_mce_up(chip);

	snd_cs4231_mce_down(chip);

	mdelay(2);

	return 0;		/* all things are ok.. */
}
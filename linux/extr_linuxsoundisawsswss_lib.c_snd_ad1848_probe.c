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
struct snd_wss {int hardware; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231P (int /*<<< orphan*/ ) ; 
 unsigned char CS4231_ENABLE_MIC_GAIN ; 
 int CS4231_INIT ; 
 int CS4231_LEFT_INPUT ; 
 int CS4231_MISC_INFO ; 
 int CS4231_MODE2 ; 
 int CS4231_RIGHT_INPUT ; 
 int CS4231_VERSION ; 
 int ENODEV ; 
 int /*<<< orphan*/  REGSEL ; 
 int /*<<< orphan*/  STATUS ; 
 unsigned short WSS_HW_AD1847 ; 
 unsigned short WSS_HW_AD1848 ; 
 unsigned short WSS_HW_CMI8330 ; 
 unsigned short WSS_HW_CS4248 ; 
 int WSS_HW_DETECT ; 
 int WSS_HW_TYPE_MASK ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  snd_wss_dout (struct snd_wss*,int,int) ; 
 int snd_wss_in (struct snd_wss*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int wss_inb (struct snd_wss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wss_outb (struct snd_wss*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ad1848_probe(struct snd_wss *chip)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);
	unsigned long flags;
	unsigned char r;
	unsigned short hardware = 0;
	int err = 0;
	int i;

	while (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT) {
		if (time_after(jiffies, timeout))
			return -ENODEV;
		cond_resched();
	}
	spin_lock_irqsave(&chip->reg_lock, flags);

	/* set CS423x MODE 1 */
	snd_wss_dout(chip, CS4231_MISC_INFO, 0);

	snd_wss_dout(chip, CS4231_RIGHT_INPUT, 0x45); /* 0x55 & ~0x10 */
	r = snd_wss_in(chip, CS4231_RIGHT_INPUT);
	if (r != 0x45) {
		/* RMGE always high on AD1847 */
		if ((r & ~CS4231_ENABLE_MIC_GAIN) != 0x45) {
			err = -ENODEV;
			goto out;
		}
		hardware = WSS_HW_AD1847;
	} else {
		snd_wss_dout(chip, CS4231_LEFT_INPUT,  0xaa);
		r = snd_wss_in(chip, CS4231_LEFT_INPUT);
		/* L/RMGE always low on AT2320 */
		if ((r | CS4231_ENABLE_MIC_GAIN) != 0xaa) {
			err = -ENODEV;
			goto out;
		}
	}

	/* clear pending IRQ */
	wss_inb(chip, CS4231P(STATUS));
	wss_outb(chip, CS4231P(STATUS), 0);
	mb();

	if ((chip->hardware & WSS_HW_TYPE_MASK) != WSS_HW_DETECT)
		goto out;

	if (hardware) {
		chip->hardware = hardware;
		goto out;
	}

	r = snd_wss_in(chip, CS4231_MISC_INFO);

	/* set CS423x MODE 2 */
	snd_wss_dout(chip, CS4231_MISC_INFO, CS4231_MODE2);
	for (i = 0; i < 16; i++) {
		if (snd_wss_in(chip, i) != snd_wss_in(chip, 16 + i)) {
			/* we have more than 16 registers: check ID */
			if ((r & 0xf) != 0xa)
				goto out_mode;
			/*
			 * on CMI8330, CS4231_VERSION is volume control and
			 * can be set to 0
			 */
			snd_wss_dout(chip, CS4231_VERSION, 0);
			r = snd_wss_in(chip, CS4231_VERSION) & 0xe7;
			if (!r)
				chip->hardware = WSS_HW_CMI8330;
			goto out_mode;
		}
	}
	if (r & 0x80)
		chip->hardware = WSS_HW_CS4248;
	else
		chip->hardware = WSS_HW_AD1848;
out_mode:
	snd_wss_dout(chip, CS4231_MISC_INFO, 0);
out:
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return err;
}
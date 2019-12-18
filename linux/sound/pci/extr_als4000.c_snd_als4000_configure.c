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
typedef  int u8 ;
struct snd_sb {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  mixer_lock; } ;

/* Variables and functions */
 int ALS4K_CR0_MX80_81_REG_WRITE_ENABLE ; 
 int /*<<< orphan*/  ALS4K_CR0_SB_CONFIG ; 
 int ALS4K_GCR8C_IRQ_MASK_CTRL_ENABLE ; 
 int ALS4K_GCR8C_MISC_CTRL ; 
 int ALS4K_GCR91_DMA0_ADDR ; 
 int ALS4K_GCR96_DMA3_MODE_COUNT ; 
 int ALS4K_GCR99_DMA_EMULATION_CTRL ; 
 int /*<<< orphan*/  SB_DMASETUP_DMA0 ; 
 int /*<<< orphan*/  SB_DSP4_DMASETUP ; 
 int snd_als4_cr_read (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_als4_cr_write (struct snd_sb*,int /*<<< orphan*/ ,int) ; 
 int snd_als4k_gcr_read (struct snd_sb*,int) ; 
 int /*<<< orphan*/  snd_als4k_gcr_write (struct snd_sb*,int,int) ; 
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_als4000_configure(struct snd_sb *chip)
{
	u8 tmp;
	int i;

	/* do some more configuration */
	spin_lock_irq(&chip->mixer_lock);
	tmp = snd_als4_cr_read(chip, ALS4K_CR0_SB_CONFIG);
	snd_als4_cr_write(chip, ALS4K_CR0_SB_CONFIG,
				tmp|ALS4K_CR0_MX80_81_REG_WRITE_ENABLE);
	/* always select DMA channel 0, since we do not actually use DMA
	 * SPECS_PAGE: 19/20 */
	snd_sbmixer_write(chip, SB_DSP4_DMASETUP, SB_DMASETUP_DMA0);
	snd_als4_cr_write(chip, ALS4K_CR0_SB_CONFIG,
				 tmp & ~ALS4K_CR0_MX80_81_REG_WRITE_ENABLE);
	spin_unlock_irq(&chip->mixer_lock);
	
	spin_lock_irq(&chip->reg_lock);
	/* enable interrupts */
	snd_als4k_gcr_write(chip, ALS4K_GCR8C_MISC_CTRL,
					ALS4K_GCR8C_IRQ_MASK_CTRL_ENABLE);

	/* SPECS_PAGE: 39 */
	for (i = ALS4K_GCR91_DMA0_ADDR; i <= ALS4K_GCR96_DMA3_MODE_COUNT; ++i)
		snd_als4k_gcr_write(chip, i, 0);
	/* enable burst mode to prevent dropouts during high PCI bus usage */
	snd_als4k_gcr_write(chip, ALS4K_GCR99_DMA_EMULATION_CTRL,
		(snd_als4k_gcr_read(chip, ALS4K_GCR99_DMA_EMULATION_CTRL) & ~0x07) | 0x04);
	spin_unlock_irq(&chip->reg_lock);
}
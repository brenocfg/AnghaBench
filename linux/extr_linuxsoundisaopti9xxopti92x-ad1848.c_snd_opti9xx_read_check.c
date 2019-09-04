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
struct snd_opti9xx {int /*<<< orphan*/ * res_mc_base; scalar_t__ mc_base; int /*<<< orphan*/  mc_base_size; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ OPTi9XX_MC_REG (int) ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * request_region (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 unsigned char snd_opti9xx_read (struct snd_opti9xx*,scalar_t__) ; 

__attribute__((used)) static int snd_opti9xx_read_check(struct snd_opti9xx *chip)
{
	unsigned char value;
#ifdef OPTi93X
	unsigned long flags;
#endif

	chip->res_mc_base = request_region(chip->mc_base, chip->mc_base_size,
					   "OPTi9xx MC");
	if (chip->res_mc_base == NULL)
		return -EBUSY;
#ifndef OPTi93X
	value = snd_opti9xx_read(chip, OPTi9XX_MC_REG(1));
	if (value != 0xff && value != inb(chip->mc_base + OPTi9XX_MC_REG(1)))
		if (value == snd_opti9xx_read(chip, OPTi9XX_MC_REG(1)))
			return 0;
#else	/* OPTi93X */
	chip->res_mc_indir = request_region(chip->mc_indir_index, 2,
					    "OPTi93x MC");
	if (chip->res_mc_indir == NULL)
		return -EBUSY;

	spin_lock_irqsave(&chip->lock, flags);
	outb(chip->password, chip->mc_base + chip->pwd_reg);
	outb(((chip->mc_indir_index & 0x1f0) >> 4), chip->mc_base);
	spin_unlock_irqrestore(&chip->lock, flags);

	value = snd_opti9xx_read(chip, OPTi9XX_MC_REG(7));
	snd_opti9xx_write(chip, OPTi9XX_MC_REG(7), 0xff - value);
	if (snd_opti9xx_read(chip, OPTi9XX_MC_REG(7)) == 0xff - value)
		return 0;

	release_and_free_resource(chip->res_mc_indir);
	chip->res_mc_indir = NULL;
#endif	/* OPTi93X */
	release_and_free_resource(chip->res_mc_base);
	chip->res_mc_base = NULL;

	return -ENODEV;
}
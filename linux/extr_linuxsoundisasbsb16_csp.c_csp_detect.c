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
struct snd_sb {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int get_version (struct snd_sb*) ; 
 unsigned char read_register (struct snd_sb*,int) ; 
 int /*<<< orphan*/  set_codec_parameter (struct snd_sb*,int,int) ; 
 int /*<<< orphan*/  set_mode_register (struct snd_sb*,int) ; 
 int /*<<< orphan*/  set_register (struct snd_sb*,int,unsigned char) ; 
 int /*<<< orphan*/  snd_sbdsp_reset (struct snd_sb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int csp_detect(struct snd_sb *chip, int *version)
{
	unsigned char csp_test1, csp_test2;
	unsigned long flags;
	int result = -ENODEV;

	spin_lock_irqsave(&chip->reg_lock, flags);

	set_codec_parameter(chip, 0x00, 0x00);
	set_mode_register(chip, 0xfc);		/* 0xfc = ?? */

	csp_test1 = read_register(chip, 0x83);
	set_register(chip, 0x83, ~csp_test1);
	csp_test2 = read_register(chip, 0x83);
	if (csp_test2 != (csp_test1 ^ 0xff))
		goto __fail;

	set_register(chip, 0x83, csp_test1);
	csp_test2 = read_register(chip, 0x83);
	if (csp_test2 != csp_test1)
		goto __fail;

	set_mode_register(chip, 0x00);		/* 0x00 = ? */

	*version = get_version(chip);
	snd_sbdsp_reset(chip);	/* reset DSP after getversion! */
	if (*version >= 0x10 && *version <= 0x1f)
		result = 0;		/* valid version id */

      __fail:
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return result;
}
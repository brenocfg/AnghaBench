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
struct snd_opti9xx {int dummy; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int OPTi9XX_HW_82C928 ; 
 int OPTi9XX_HW_82C930 ; 
 int snd_opti9xx_init (struct snd_opti9xx*,int) ; 
 int snd_opti9xx_read_check (struct snd_opti9xx*) ; 

__attribute__((used)) static int snd_card_opti9xx_detect(struct snd_card *card,
				   struct snd_opti9xx *chip)
{
	int i, err;

#ifndef OPTi93X
	for (i = OPTi9XX_HW_82C928; i < OPTi9XX_HW_82C930; i++) {
#else
	for (i = OPTi9XX_HW_82C931; i >= OPTi9XX_HW_82C930; i--) {
#endif
		err = snd_opti9xx_init(chip, i);
		if (err < 0)
			return err;

		err = snd_opti9xx_read_check(chip);
		if (err == 0)
			return 1;
#ifdef OPTi93X
		chip->mc_indir_index = 0;
#endif
	}
	return -ENODEV;
}
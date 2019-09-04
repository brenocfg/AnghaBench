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
struct snd_miro {int dummy; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int OPTi9XX_HW_82C924 ; 
 int OPTi9XX_HW_82C929 ; 
 int snd_miro_init (struct snd_miro*,int) ; 
 int snd_miro_opti_check (struct snd_miro*) ; 

__attribute__((used)) static int snd_card_miro_detect(struct snd_card *card,
				struct snd_miro *chip)
{
	int i, err;

	for (i = OPTi9XX_HW_82C929; i <= OPTi9XX_HW_82C924; i++) {

		if ((err = snd_miro_init(chip, i)) < 0)
			return err;

		err = snd_miro_opti_check(chip);
		if (err == 0)
			return 1;
	}

	return -ENODEV;
}
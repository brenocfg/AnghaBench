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
struct snd_mixart {TYPE_1__* mgr; } ;
struct TYPE_2__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ MIXART_DAUGHTER_TYPE_AES ; 
 int snd_mixart_pcm_analog (struct snd_mixart*) ; 
 int snd_mixart_pcm_digital (struct snd_mixart*) ; 

int snd_mixart_create_pcm(struct snd_mixart* chip)
{
	int err;

	err = snd_mixart_pcm_analog(chip);
	if (err < 0)
		return err;

	if(chip->mgr->board_type == MIXART_DAUGHTER_TYPE_AES) {

		err = snd_mixart_pcm_digital(chip);
		if (err < 0)
			return err;
	}
	return err;
}
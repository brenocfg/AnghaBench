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
struct snd_sh_dac {struct snd_sh_dac* data_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_sh_dac*) ; 

__attribute__((used)) static int snd_sh_dac_free(struct snd_sh_dac *chip)
{
	/* release the data */
	kfree(chip->data_buffer);
	kfree(chip);

	return 0;
}
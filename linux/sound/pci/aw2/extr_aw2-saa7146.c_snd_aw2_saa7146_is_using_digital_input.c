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
struct snd_aw2_saa7146 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CTRL ; 
 unsigned int READREG (int /*<<< orphan*/ ) ; 

int snd_aw2_saa7146_is_using_digital_input(struct snd_aw2_saa7146 *chip)
{
	unsigned int reg_val = READREG(GPIO_CTRL);
	if ((reg_val & 0xFF) == 0x40)
		return 1;
	else
		return 0;
}
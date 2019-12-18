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
struct snd_es1688 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_AVAIL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ES1688P (struct snd_es1688*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printd (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_es1688_dsp_get_byte(struct snd_es1688 *chip)
{
	int i;

	for (i = 1000; i; i--)
		if (inb(ES1688P(chip, DATA_AVAIL)) & 0x80)
			return inb(ES1688P(chip, READ));
	snd_printd("es1688 get byte failed: 0x%lx = 0x%x!!!\n", ES1688P(chip, DATA_AVAIL), inb(ES1688P(chip, DATA_AVAIL)));
	return -ENODEV;
}
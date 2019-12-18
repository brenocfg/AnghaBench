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
struct snd_sb {int dummy; } ;

/* Variables and functions */
 int command_seq (struct snd_sb*,unsigned char*,int) ; 

__attribute__((used)) static int set_register(struct snd_sb *chip, unsigned char reg, unsigned char val)
{
	unsigned char dsp_cmd[3];

	dsp_cmd[0] = 0x0e;	/* CSP set register */
	dsp_cmd[1] = reg;	/* CSP Register */
	dsp_cmd[2] = val;	/* value */
	return command_seq(chip, dsp_cmd, 3);
}
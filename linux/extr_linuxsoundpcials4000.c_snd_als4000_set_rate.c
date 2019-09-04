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
struct snd_sb {int mode; } ;

/* Variables and functions */
 unsigned int SB_DSP_SAMPLE_RATE_OUT ; 
 int SB_RATE_LOCK ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,unsigned int) ; 

__attribute__((used)) static void snd_als4000_set_rate(struct snd_sb *chip, unsigned int rate)
{
	if (!(chip->mode & SB_RATE_LOCK)) {
		snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE_OUT);
		snd_sbdsp_command(chip, rate>>8);
		snd_sbdsp_command(chip, rate);
	}
}
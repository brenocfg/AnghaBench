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
struct snd_cs46xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_EGPIODR ; 
 int /*<<< orphan*/  BA0_EGPIOPTR ; 
 int /*<<< orphan*/  EGPIODR_GPOE0 ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hercules_init(struct snd_cs46xx *chip) 
{
	/* default: AMP off, and SPDIF input optical */
	snd_cs46xx_pokeBA0(chip, BA0_EGPIODR, EGPIODR_GPOE0);
	snd_cs46xx_pokeBA0(chip, BA0_EGPIOPTR, EGPIODR_GPOE0);
}
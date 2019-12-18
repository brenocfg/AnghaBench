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
struct cs4281 {int midcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_MIDCR ; 
 int BA0_MIDCR_MRST ; 
 int /*<<< orphan*/  snd_cs4281_pokeBA0 (struct cs4281*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_cs4281_midi_reset(struct cs4281 *chip)
{
	snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr | BA0_MIDCR_MRST);
	udelay(100);
	snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
}
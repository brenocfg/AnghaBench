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
struct snd_emu8000 {int /*<<< orphan*/  port1; } ;

/* Variables and functions */
 int EMU8000_HWCF1_READ (struct snd_emu8000*) ; 
 int /*<<< orphan*/  EMU8000_HWCF1_WRITE (struct snd_emu8000*,int) ; 
 int EMU8000_HWCF2_READ (struct snd_emu8000*) ; 
 int /*<<< orphan*/  EMU8000_HWCF2_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  EMU8000_HWCF3_WRITE (struct snd_emu8000*,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_emu8000_detect(struct snd_emu8000 *emu)
{
	/* Initialise */
	EMU8000_HWCF1_WRITE(emu, 0x0059);
	EMU8000_HWCF2_WRITE(emu, 0x0020);
	EMU8000_HWCF3_WRITE(emu, 0x0000);
	/* Check for a recognisable emu8000 */
	/*
	if ((EMU8000_U1_READ(emu) & 0x000f) != 0x000c)
		return -ENODEV;
		*/
	if ((EMU8000_HWCF1_READ(emu) & 0x007e) != 0x0058)
		return -ENODEV;
	if ((EMU8000_HWCF2_READ(emu) & 0x0003) != 0x0003)
		return -ENODEV;

	snd_printdd("EMU8000 [0x%lx]: Synth chip found\n",
                    emu->port1);
	return 0;
}
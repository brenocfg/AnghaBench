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
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_HWCF4_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMU8000_HWCF5_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  EMU8000_HWCF6_WRITE (struct snd_emu8000*,int) ; 
 int /*<<< orphan*/  init1 ; 
 int /*<<< orphan*/  init2 ; 
 int /*<<< orphan*/  init3 ; 
 int /*<<< orphan*/  init4 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  send_array (struct snd_emu8000*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_arrays(struct snd_emu8000 *emu)
{
	send_array(emu, init1, ARRAY_SIZE(init1)/4);

	msleep((1024 * 1000) / 44100); /* wait for 1024 clocks */
	send_array(emu, init2, ARRAY_SIZE(init2)/4);
	send_array(emu, init3, ARRAY_SIZE(init3)/4);

	EMU8000_HWCF4_WRITE(emu, 0);
	EMU8000_HWCF5_WRITE(emu, 0x83);
	EMU8000_HWCF6_WRITE(emu, 0x8000);

	send_array(emu, init4, ARRAY_SIZE(init4)/4);
}
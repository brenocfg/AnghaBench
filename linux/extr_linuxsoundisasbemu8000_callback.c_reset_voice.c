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
struct snd_emux {struct snd_emu8000* hw; } ;
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int,int) ; 
 int /*<<< orphan*/  snd_emu8000_tweak_voice (struct snd_emu8000*,int) ; 

__attribute__((used)) static void
reset_voice(struct snd_emux *emu, int ch)
{
	struct snd_emu8000 *hw;

	hw = emu->hw;
	EMU8000_DCYSUSV_WRITE(hw, ch, 0x807F);
	snd_emu8000_tweak_voice(hw, ch);
}
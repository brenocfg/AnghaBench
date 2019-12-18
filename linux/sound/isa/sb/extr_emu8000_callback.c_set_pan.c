#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ loopstart; } ;
struct snd_emux_voice {int /*<<< orphan*/  ch; TYPE_1__ reg; scalar_t__ apan; } ;
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_PSST_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
set_pan(struct snd_emu8000 *hw, struct snd_emux_voice *vp)
{
	unsigned int temp;

	temp = ((unsigned int)vp->apan<<24) | ((unsigned int)vp->reg.loopstart - 1);
	EMU8000_PSST_WRITE(hw, vp->ch, temp);
}
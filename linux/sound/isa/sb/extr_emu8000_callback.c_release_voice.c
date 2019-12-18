#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ volrelease; scalar_t__ modrelease; } ;
struct TYPE_4__ {TYPE_1__ parm; } ;
struct snd_emux_voice {int /*<<< orphan*/  ch; TYPE_2__ reg; struct snd_emu8000* hw; } ;
struct snd_emu8000 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMU8000_DCYSUSV_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EMU8000_DCYSUS_WRITE (struct snd_emu8000*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
release_voice(struct snd_emux_voice *vp)
{
	int dcysusv;
	struct snd_emu8000 *hw;

	hw = vp->hw;
	dcysusv = 0x8000 | (unsigned char)vp->reg.parm.modrelease;
	EMU8000_DCYSUS_WRITE(hw, vp->ch, dcysusv);
	dcysusv = 0x8000 | (unsigned char)vp->reg.parm.volrelease;
	EMU8000_DCYSUSV_WRITE(hw, vp->ch, dcysusv);
}
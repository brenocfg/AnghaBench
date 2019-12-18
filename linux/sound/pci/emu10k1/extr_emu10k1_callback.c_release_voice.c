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
struct snd_emux_voice {int /*<<< orphan*/  ch; TYPE_2__ reg; struct snd_emu10k1* hw; } ;
struct snd_emu10k1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCYSUSM ; 
 int /*<<< orphan*/  DCYSUSV ; 
 int DCYSUSV_CHANNELENABLE_MASK ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
release_voice(struct snd_emux_voice *vp)
{
	int dcysusv;
	struct snd_emu10k1 *hw;
	
	hw = vp->hw;
	dcysusv = 0x8000 | (unsigned char)vp->reg.parm.modrelease;
	snd_emu10k1_ptr_write(hw, DCYSUSM, vp->ch, dcysusv);
	dcysusv = 0x8000 | (unsigned char)vp->reg.parm.volrelease | DCYSUSV_CHANNELENABLE_MASK;
	snd_emu10k1_ptr_write(hw, DCYSUSV, vp->ch, dcysusv);
}
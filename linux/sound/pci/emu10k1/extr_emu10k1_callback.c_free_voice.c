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
struct snd_emux_voice {size_t ch; TYPE_1__* emu; struct snd_emu10k1* hw; } ;
struct snd_emu10k1 {int /*<<< orphan*/ * voices; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_voices; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVCF ; 
 int /*<<< orphan*/  DCYSUSV ; 
 int DCYSUSV_CHANNELENABLE_MASK ; 
 int /*<<< orphan*/  IFATN ; 
 int /*<<< orphan*/  VTFT ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  snd_emu10k1_voice_free (struct snd_emu10k1*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_voice(struct snd_emux_voice *vp)
{
	struct snd_emu10k1 *hw;
	
	hw = vp->hw;
	/* FIXME: emu10k1_synth is broken. */
	/* This can get called with hw == 0 */
	/* Problem apparent on plug, unplug then plug */
	/* on the Audigy 2 ZS Notebook. */
	if (hw && (vp->ch >= 0)) {
		snd_emu10k1_ptr_write(hw, IFATN, vp->ch, 0xff00);
		snd_emu10k1_ptr_write(hw, DCYSUSV, vp->ch, 0x807f | DCYSUSV_CHANNELENABLE_MASK);
		// snd_emu10k1_ptr_write(hw, DCYSUSV, vp->ch, 0);
		snd_emu10k1_ptr_write(hw, VTFT, vp->ch, 0xffff);
		snd_emu10k1_ptr_write(hw, CVCF, vp->ch, 0xffff);
		snd_emu10k1_voice_free(hw, &hw->voices[vp->ch]);
		vp->emu->num_voices--;
		vp->ch = -1;
	}
}
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
struct snd_emux_voice {scalar_t__ block; int /*<<< orphan*/  ch; struct snd_emu10k1* hw; } ;
struct snd_emu10k1_memblk {scalar_t__ map_locked; } ;
struct snd_emu10k1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCYSUSV ; 
 int DCYSUSV_CHANNELENABLE_MASK ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
terminate_voice(struct snd_emux_voice *vp)
{
	struct snd_emu10k1 *hw;
	
	if (snd_BUG_ON(!vp))
		return;
	hw = vp->hw;
	snd_emu10k1_ptr_write(hw, DCYSUSV, vp->ch, 0x807f | DCYSUSV_CHANNELENABLE_MASK);
	if (vp->block) {
		struct snd_emu10k1_memblk *emem;
		emem = (struct snd_emu10k1_memblk *)vp->block;
		if (emem->map_locked > 0)
			emem->map_locked--;
	}
}
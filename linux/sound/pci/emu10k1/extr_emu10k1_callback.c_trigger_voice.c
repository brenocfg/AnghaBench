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
struct TYPE_3__ {unsigned int voldcysus; } ;
struct TYPE_4__ {TYPE_1__ parm; } ;
struct snd_emux_voice {int apan; unsigned int aaux; TYPE_2__ reg; int /*<<< orphan*/  ch; int /*<<< orphan*/  apitch; scalar_t__ ptarget; scalar_t__ block; struct snd_emu10k1* hw; } ;
struct snd_emu10k1_memblk {scalar_t__ mapped_page; } ;
struct snd_emu10k1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPF ; 
 int /*<<< orphan*/  DCYSUSV ; 
 unsigned int DCYSUSV_CHANNELENABLE_MASK ; 
 unsigned int IP_TO_CP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRX ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
trigger_voice(struct snd_emux_voice *vp)
{
	unsigned int temp, ptarget;
	struct snd_emu10k1 *hw;
	struct snd_emu10k1_memblk *emem;
	
	hw = vp->hw;

	emem = (struct snd_emu10k1_memblk *)vp->block;
	if (! emem || emem->mapped_page < 0)
		return; /* not mapped */

#if 0
	ptarget = (unsigned int)vp->ptarget << 16;
#else
	ptarget = IP_TO_CP(vp->apitch);
#endif
	/* set pitch target and pan (volume) */
	temp = ptarget | (vp->apan << 8) | vp->aaux;
	snd_emu10k1_ptr_write(hw, PTRX, vp->ch, temp);

	/* pitch target */
	snd_emu10k1_ptr_write(hw, CPF, vp->ch, ptarget);

	/* trigger voice */
	snd_emu10k1_ptr_write(hw, DCYSUSV, vp->ch, vp->reg.parm.voldcysus|DCYSUSV_CHANNELENABLE_MASK);
}
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
struct TYPE_3__ {int filterQ; } ;
struct TYPE_4__ {TYPE_1__ parm; } ;
struct snd_emux_voice {int /*<<< orphan*/  ch; TYPE_2__ reg; } ;
struct snd_emu10k1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCCA ; 
 unsigned int CCCA_RESONANCE ; 
 unsigned int snd_emu10k1_ptr_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
set_filterQ(struct snd_emu10k1 *hw, struct snd_emux_voice *vp)
{
	unsigned int val;
	val = snd_emu10k1_ptr_read(hw, CCCA, vp->ch) & ~CCCA_RESONANCE;
	val |= (vp->reg.parm.filterQ << 28);
	snd_emu10k1_ptr_write(hw, CCCA, vp->ch, val);
}
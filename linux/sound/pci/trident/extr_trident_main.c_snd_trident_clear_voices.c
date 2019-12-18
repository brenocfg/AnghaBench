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
struct snd_trident {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  T4D_AINTEN_A ; 
 int /*<<< orphan*/  T4D_AINTEN_B ; 
 int /*<<< orphan*/  T4D_STOP_A ; 
 int /*<<< orphan*/  T4D_STOP_B ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,int /*<<< orphan*/ ) ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static void snd_trident_clear_voices(struct snd_trident * trident, unsigned short v_min, unsigned short v_max)
{
	unsigned int i, val, mask[2] = { 0, 0 };

	if (snd_BUG_ON(v_min > 63 || v_max > 63))
		return;
	for (i = v_min; i <= v_max; i++)
		mask[i >> 5] |= 1 << (i & 0x1f);
	if (mask[0]) {
		outl(mask[0], TRID_REG(trident, T4D_STOP_A));
		val = inl(TRID_REG(trident, T4D_AINTEN_A));
		outl(val & ~mask[0], TRID_REG(trident, T4D_AINTEN_A));
	}
	if (mask[1]) {
		outl(mask[1], TRID_REG(trident, T4D_STOP_B));
		val = inl(TRID_REG(trident, T4D_AINTEN_B));
		outl(val & ~mask[1], TRID_REG(trident, T4D_AINTEN_B));
	}
}
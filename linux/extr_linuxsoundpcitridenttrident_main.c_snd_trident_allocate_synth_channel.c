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
struct TYPE_2__ {int /*<<< orphan*/  ChanSynthCount; } ;
struct snd_trident {int* ChanMap; TYPE_1__ synth; } ;

/* Variables and functions */
 size_t T4D_BANK_A ; 

__attribute__((used)) static int snd_trident_allocate_synth_channel(struct snd_trident * trident)
{
	int idx;

	for (idx = 31; idx >= 0; idx--) {
		if (!(trident->ChanMap[T4D_BANK_A] & (1 << idx))) {
			trident->ChanMap[T4D_BANK_A] |= 1 << idx;
			trident->synth.ChanSynthCount++;
			return idx;
		}
	}
	return -1;
}
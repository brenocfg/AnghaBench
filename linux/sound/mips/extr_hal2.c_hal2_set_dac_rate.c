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
struct TYPE_2__ {unsigned int master; int inc; int mod; } ;
struct snd_hal2 {TYPE_1__ dac; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2I_BRES1_C1 ; 
 int /*<<< orphan*/  H2I_BRES1_C2 ; 
 int /*<<< orphan*/  hal2_i_write16 (struct snd_hal2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hal2_i_write32 (struct snd_hal2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hal2_set_dac_rate(struct snd_hal2 *hal2)
{
	unsigned int master = hal2->dac.master;
	int inc = hal2->dac.inc;
	int mod = hal2->dac.mod;

	hal2_i_write16(hal2, H2I_BRES1_C1, (master == 44100) ? 1 : 0);
	hal2_i_write32(hal2, H2I_BRES1_C2,
		       ((0xffff & (inc - mod - 1)) << 16) | inc);
}
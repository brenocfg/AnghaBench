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

/* Variables and functions */
 int ALLO_BOSS_CLK44EN ; 
 int ALLO_BOSS_CLK48EN ; 

__attribute__((used)) static int snd_allo_boss_clk_for_rate(int sample_rate)
{
	int type;

	switch (sample_rate) {
	case 11025:
	case 22050:
	case 44100:
	case 88200:
	case 176400:
	case 352800:
		type = ALLO_BOSS_CLK44EN;
		break;
	default:
		type = ALLO_BOSS_CLK48EN;
		break;
	}
	return type;
}
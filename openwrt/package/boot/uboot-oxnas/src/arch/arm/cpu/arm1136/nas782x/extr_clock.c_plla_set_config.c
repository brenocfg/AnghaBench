#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mhz; int /*<<< orphan*/  sslope; int /*<<< orphan*/  sfreq; int /*<<< orphan*/  bwadj; int /*<<< orphan*/  fbdiv; int /*<<< orphan*/  refdiv; int /*<<< orphan*/  outdiv; } ;
typedef  TYPE_1__ PLL_CONFIG ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* C_PLL_CONFIG ; 
 int PLL_FREQ_STEP ; 
 int PLL_LOW_FREQ ; 
 int /*<<< orphan*/  debug (char*,int) ; 
 int /*<<< orphan*/  plla_configure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

int plla_set_config(int mhz)
{
	int index = (mhz - PLL_LOW_FREQ) / PLL_FREQ_STEP;
	const PLL_CONFIG *cfg;

	if (index < 0 || index > ARRAY_SIZE(C_PLL_CONFIG)) {
		debug("Freq %d MHz out of range, default to lowest\n", mhz);
		index = 0;
	}
	cfg = &C_PLL_CONFIG[index];

	printf("Attempting to set PLLA to %d MHz ...\n", (unsigned) cfg->mhz);
	plla_configure(cfg->outdiv, cfg->refdiv, cfg->fbdiv, cfg->bwadj,
	               cfg->sfreq, cfg->sslope);

	return cfg->mhz;
}
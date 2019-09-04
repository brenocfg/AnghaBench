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
struct arizona_fll {int id; int base; unsigned int ref_src; int ref_freq; int /*<<< orphan*/  clock_ok_name; int /*<<< orphan*/  lock_name; void* sync_src; struct arizona* arizona; } ;
struct arizona {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int ARIZONA_CLK_32K_SRC_MASK ; 
#define  ARIZONA_CLK_SRC_MCLK1 129 
#define  ARIZONA_CLK_SRC_MCLK2 128 
 int /*<<< orphan*/  ARIZONA_CLOCK_32K_1 ; 
 int /*<<< orphan*/  ARIZONA_FLL1_FREERUN ; 
 void* ARIZONA_FLL_SRC_NONE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

int arizona_init_fll(struct arizona *arizona, int id, int base, int lock_irq,
		     int ok_irq, struct arizona_fll *fll)
{
	unsigned int val;

	fll->id = id;
	fll->base = base;
	fll->arizona = arizona;
	fll->sync_src = ARIZONA_FLL_SRC_NONE;

	/* Configure default refclk to 32kHz if we have one */
	regmap_read(arizona->regmap, ARIZONA_CLOCK_32K_1, &val);
	switch (val & ARIZONA_CLK_32K_SRC_MASK) {
	case ARIZONA_CLK_SRC_MCLK1:
	case ARIZONA_CLK_SRC_MCLK2:
		fll->ref_src = val & ARIZONA_CLK_32K_SRC_MASK;
		break;
	default:
		fll->ref_src = ARIZONA_FLL_SRC_NONE;
	}
	fll->ref_freq = 32768;

	snprintf(fll->lock_name, sizeof(fll->lock_name), "FLL%d lock", id);
	snprintf(fll->clock_ok_name, sizeof(fll->clock_ok_name),
		 "FLL%d clock OK", id);

	regmap_update_bits(arizona->regmap, fll->base + 1,
			   ARIZONA_FLL1_FREERUN, 0);

	return 0;
}
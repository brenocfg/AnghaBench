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
struct madera_fll {int id; int base; void* sync_src; void* ref_src; struct madera* madera; } ;
struct madera {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_FLL1_FREERUN ; 
 scalar_t__ MADERA_FLL_CONTROL_1_OFFS ; 
 void* MADERA_FLL_SRC_NONE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int madera_init_fll(struct madera *madera, int id, int base,
		    struct madera_fll *fll)
{
	fll->id = id;
	fll->base = base;
	fll->madera = madera;
	fll->ref_src = MADERA_FLL_SRC_NONE;
	fll->sync_src = MADERA_FLL_SRC_NONE;

	regmap_update_bits(madera->regmap,
			   fll->base + MADERA_FLL_CONTROL_1_OFFS,
			   MADERA_FLL1_FREERUN, 0);

	return 0;
}
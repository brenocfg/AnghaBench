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
struct madera_fll_gains {unsigned int min; unsigned int max; int /*<<< orphan*/  alt_gain; int /*<<< orphan*/  gain; } ;
struct madera_fll_cfg {int /*<<< orphan*/  alt_gain; int /*<<< orphan*/  gain; } ;
struct madera_fll {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  madera_fll_err (struct madera_fll*,char*,unsigned int) ; 

__attribute__((used)) static int madera_find_fll_gain(struct madera_fll *fll,
				struct madera_fll_cfg *cfg,
				unsigned int fref,
				const struct madera_fll_gains *gains,
				int n_gains)
{
	int i;

	for (i = 0; i < n_gains; i++) {
		if (gains[i].min <= fref && fref <= gains[i].max) {
			cfg->gain = gains[i].gain;
			cfg->alt_gain = gains[i].alt_gain;
			return 0;
		}
	}

	madera_fll_err(fll, "Unable to find gain for fref=%uHz\n", fref);

	return -EINVAL;
}
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
struct snd_soc_component {int dummy; } ;
struct cs47l92 {int /*<<< orphan*/ * fll; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MADERA_FLL1_REFCLK 129 
#define  MADERA_FLL2_REFCLK 128 
 int madera_fllhj_set_refclk (int /*<<< orphan*/ *,int,unsigned int,unsigned int) ; 
 struct cs47l92* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs47l92_set_fll(struct snd_soc_component *component, int fll_id,
			   int source, unsigned int fref, unsigned int fout)
{
	struct cs47l92 *cs47l92 = snd_soc_component_get_drvdata(component);

	switch (fll_id) {
	case MADERA_FLL1_REFCLK:
		return madera_fllhj_set_refclk(&cs47l92->fll[0], source, fref,
					       fout);
	case MADERA_FLL2_REFCLK:
		return madera_fllhj_set_refclk(&cs47l92->fll[1], source, fref,
					       fout);
	default:
		return -EINVAL;
	}
}
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
struct cs47l24_priv {int /*<<< orphan*/ * fll; } ;

/* Variables and functions */
#define  CS47L24_FLL1 131 
#define  CS47L24_FLL1_REFCLK 130 
#define  CS47L24_FLL2 129 
#define  CS47L24_FLL2_REFCLK 128 
 int EINVAL ; 
 int arizona_set_fll (int /*<<< orphan*/ *,int,unsigned int,unsigned int) ; 
 int arizona_set_fll_refclk (int /*<<< orphan*/ *,int,unsigned int,unsigned int) ; 
 struct cs47l24_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs47l24_set_fll(struct snd_soc_component *component, int fll_id,
			   int source, unsigned int Fref, unsigned int Fout)
{
	struct cs47l24_priv *cs47l24 = snd_soc_component_get_drvdata(component);

	switch (fll_id) {
	case CS47L24_FLL1:
		return arizona_set_fll(&cs47l24->fll[0], source, Fref, Fout);
	case CS47L24_FLL2:
		return arizona_set_fll(&cs47l24->fll[1], source, Fref, Fout);
	case CS47L24_FLL1_REFCLK:
		return arizona_set_fll_refclk(&cs47l24->fll[0], source, Fref,
					      Fout);
	case CS47L24_FLL2_REFCLK:
		return arizona_set_fll_refclk(&cs47l24->fll[1], source, Fref,
					      Fout);
	default:
		return -EINVAL;
	}
}
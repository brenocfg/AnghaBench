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
struct wm5110_priv {int /*<<< orphan*/ * fll; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM5110_FLL1 131 
#define  WM5110_FLL1_REFCLK 130 
#define  WM5110_FLL2 129 
#define  WM5110_FLL2_REFCLK 128 
 int arizona_set_fll (int /*<<< orphan*/ *,int,unsigned int,unsigned int) ; 
 int arizona_set_fll_refclk (int /*<<< orphan*/ *,int,unsigned int,unsigned int) ; 
 struct wm5110_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm5110_set_fll(struct snd_soc_component *component, int fll_id,
			  int source, unsigned int Fref, unsigned int Fout)
{
	struct wm5110_priv *wm5110 = snd_soc_component_get_drvdata(component);

	switch (fll_id) {
	case WM5110_FLL1:
		return arizona_set_fll(&wm5110->fll[0], source, Fref, Fout);
	case WM5110_FLL2:
		return arizona_set_fll(&wm5110->fll[1], source, Fref, Fout);
	case WM5110_FLL1_REFCLK:
		return arizona_set_fll_refclk(&wm5110->fll[0], source, Fref,
					      Fout);
	case WM5110_FLL2_REFCLK:
		return arizona_set_fll_refclk(&wm5110->fll[1], source, Fref,
					      Fout);
	default:
		return -EINVAL;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct da9055_priv {scalar_t__ master; } ;
struct TYPE_3__ {unsigned int fref; scalar_t__ mode; unsigned int fout; size_t frac_top; size_t frac_bot; size_t integer; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DA9055_PLL_CTRL ; 
 int /*<<< orphan*/  DA9055_PLL_EN ; 
 int /*<<< orphan*/  DA9055_PLL_FRAC_BOT ; 
 int /*<<< orphan*/  DA9055_PLL_FRAC_TOP ; 
 int /*<<< orphan*/  DA9055_PLL_INTEGER ; 
 int EINVAL ; 
 TYPE_1__* da9055_pll_div ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct da9055_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int da9055_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
			      int source, unsigned int fref, unsigned int fout)
{
	struct snd_soc_component *component = codec_dai->component;
	struct da9055_priv *da9055 = snd_soc_component_get_drvdata(component);

	u8 pll_frac_top, pll_frac_bot, pll_integer, cnt;

	/* Disable PLL before setting the divisors */
	snd_soc_component_update_bits(component, DA9055_PLL_CTRL, DA9055_PLL_EN, 0);

	/* In slave mode, there is only one set of divisors */
	if (!da9055->master && (fout != 2822400))
		goto pll_err;

	/* Search pll div array for correct divisors */
	for (cnt = 0; cnt < ARRAY_SIZE(da9055_pll_div); cnt++) {
		/* Check fref, mode  and fout */
		if ((fref == da9055_pll_div[cnt].fref) &&
		    (da9055->master ==  da9055_pll_div[cnt].mode) &&
		    (fout == da9055_pll_div[cnt].fout)) {
			/* All match, pick up divisors */
			pll_frac_top = da9055_pll_div[cnt].frac_top;
			pll_frac_bot = da9055_pll_div[cnt].frac_bot;
			pll_integer = da9055_pll_div[cnt].integer;
			break;
		}
	}
	if (cnt >= ARRAY_SIZE(da9055_pll_div))
		goto pll_err;

	/* Write PLL dividers */
	snd_soc_component_write(component, DA9055_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_component_write(component, DA9055_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_component_write(component, DA9055_PLL_INTEGER, pll_integer);

	return 0;
pll_err:
	dev_err(codec_dai->dev, "Error in setting up PLL\n");
	return -EINVAL;
}
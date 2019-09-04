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
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct adav80x {int clk_src; } ;

/* Variables and functions */
#define  ADAV80X_CLK_PLL1 130 
#define  ADAV80X_CLK_PLL2 129 
#define  ADAV80X_CLK_XTAL 128 
 struct adav80x* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int adav80x_dapm_sysclk_check(struct snd_soc_dapm_widget *source,
			 struct snd_soc_dapm_widget *sink)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	struct adav80x *adav80x = snd_soc_component_get_drvdata(component);
	const char *clk;

	switch (adav80x->clk_src) {
	case ADAV80X_CLK_PLL1:
		clk = "PLL1";
		break;
	case ADAV80X_CLK_PLL2:
		clk = "PLL2";
		break;
	case ADAV80X_CLK_XTAL:
		clk = "OSC";
		break;
	default:
		return 0;
	}

	return strcmp(source->name, clk) == 0;
}
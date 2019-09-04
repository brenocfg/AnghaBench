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
struct wm8988_priv {unsigned int sysclk; int /*<<< orphan*/ * sysclk_constraints; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  constraints_112896 ; 
 int /*<<< orphan*/  constraints_12 ; 
 int /*<<< orphan*/  constraints_12288 ; 
 struct wm8988_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8988_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct wm8988_priv *wm8988 = snd_soc_component_get_drvdata(component);

	switch (freq) {
	case 11289600:
	case 18432000:
	case 22579200:
	case 36864000:
		wm8988->sysclk_constraints = &constraints_112896;
		wm8988->sysclk = freq;
		return 0;

	case 12288000:
	case 16934400:
	case 24576000:
	case 33868800:
		wm8988->sysclk_constraints = &constraints_12288;
		wm8988->sysclk = freq;
		return 0;

	case 12000000:
	case 24000000:
		wm8988->sysclk_constraints = &constraints_12;
		wm8988->sysclk = freq;
		return 0;
	}
	return -EINVAL;
}
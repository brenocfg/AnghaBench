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
struct snd_ac97_reset_cfg {int gpio_sync; int gpio_sdata; int gpio_reset; struct pinctrl_state* pstate_run; struct pinctrl_state* pstate_warm_reset; struct pinctrl_state* pstate_reset; struct pinctrl_state* pctl; } ;
struct pinctrl_state {int dummy; } ;
typedef  struct pinctrl_state pinctrl ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
 int PTR_ERR (struct pinctrl_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_gpio_request (struct device*,int,char*) ; 
 struct pinctrl_state* devm_pinctrl_get (struct device*) ; 
 int of_get_named_gpio (int /*<<< orphan*/ ,char*,int) ; 
 struct pinctrl_state* pinctrl_lookup_state (struct pinctrl_state*,char*) ; 

__attribute__((used)) static int snd_soc_ac97_parse_pinctl(struct device *dev,
		struct snd_ac97_reset_cfg *cfg)
{
	struct pinctrl *p;
	struct pinctrl_state *state;
	int gpio;
	int ret;

	p = devm_pinctrl_get(dev);
	if (IS_ERR(p)) {
		dev_err(dev, "Failed to get pinctrl\n");
		return PTR_ERR(p);
	}
	cfg->pctl = p;

	state = pinctrl_lookup_state(p, "ac97-reset");
	if (IS_ERR(state)) {
		dev_err(dev, "Can't find pinctrl state ac97-reset\n");
		return PTR_ERR(state);
	}
	cfg->pstate_reset = state;

	state = pinctrl_lookup_state(p, "ac97-warm-reset");
	if (IS_ERR(state)) {
		dev_err(dev, "Can't find pinctrl state ac97-warm-reset\n");
		return PTR_ERR(state);
	}
	cfg->pstate_warm_reset = state;

	state = pinctrl_lookup_state(p, "ac97-running");
	if (IS_ERR(state)) {
		dev_err(dev, "Can't find pinctrl state ac97-running\n");
		return PTR_ERR(state);
	}
	cfg->pstate_run = state;

	gpio = of_get_named_gpio(dev->of_node, "ac97-gpios", 0);
	if (gpio < 0) {
		dev_err(dev, "Can't find ac97-sync gpio\n");
		return gpio;
	}
	ret = devm_gpio_request(dev, gpio, "AC97 link sync");
	if (ret) {
		dev_err(dev, "Failed requesting ac97-sync gpio\n");
		return ret;
	}
	cfg->gpio_sync = gpio;

	gpio = of_get_named_gpio(dev->of_node, "ac97-gpios", 1);
	if (gpio < 0) {
		dev_err(dev, "Can't find ac97-sdata gpio %d\n", gpio);
		return gpio;
	}
	ret = devm_gpio_request(dev, gpio, "AC97 link sdata");
	if (ret) {
		dev_err(dev, "Failed requesting ac97-sdata gpio\n");
		return ret;
	}
	cfg->gpio_sdata = gpio;

	gpio = of_get_named_gpio(dev->of_node, "ac97-gpios", 2);
	if (gpio < 0) {
		dev_err(dev, "Can't find ac97-reset gpio\n");
		return gpio;
	}
	ret = devm_gpio_request(dev, gpio, "AC97 link reset");
	if (ret) {
		dev_err(dev, "Failed requesting ac97-reset gpio\n");
		return ret;
	}
	cfg->gpio_reset = gpio;

	return 0;
}
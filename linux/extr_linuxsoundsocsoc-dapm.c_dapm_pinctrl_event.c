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
struct snd_soc_dapm_widget {struct pinctrl* pinctrl; struct snd_soc_dapm_pinctrl_priv* priv; } ;
struct snd_soc_dapm_pinctrl_priv {int /*<<< orphan*/  sleep_state; int /*<<< orphan*/  active_state; } ;
struct snd_kcontrol {int dummy; } ;
struct pinctrl_state {int dummy; } ;
struct pinctrl {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
 int PTR_ERR (struct pinctrl_state*) ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 struct pinctrl_state* pinctrl_lookup_state (struct pinctrl*,int /*<<< orphan*/ ) ; 
 int pinctrl_select_state (struct pinctrl*,struct pinctrl_state*) ; 

int dapm_pinctrl_event(struct snd_soc_dapm_widget *w,
		       struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_dapm_pinctrl_priv *priv = w->priv;
	struct pinctrl *p = w->pinctrl;
	struct pinctrl_state *s;

	if (!p || !priv)
		return -EIO;

	if (SND_SOC_DAPM_EVENT_ON(event))
		s = pinctrl_lookup_state(p, priv->active_state);
	else
		s = pinctrl_lookup_state(p, priv->sleep_state);

	if (IS_ERR(s))
		return PTR_ERR(s);

	return pinctrl_select_state(p, s);
}
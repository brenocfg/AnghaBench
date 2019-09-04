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
struct wm8524_priv {int /*<<< orphan*/  mute; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wm8524_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void wm8524_shutdown(struct snd_pcm_substream *substream,
			  struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct wm8524_priv *wm8524 = snd_soc_component_get_drvdata(component);

	gpiod_set_value_cansleep(wm8524->mute, 0);
}
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
struct wm8524_priv {scalar_t__ mute; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 struct wm8524_priv* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8524_mute_stream(struct snd_soc_dai *dai, int mute, int stream)
{
	struct wm8524_priv *wm8524 = snd_soc_component_get_drvdata(dai->component);

	if (wm8524->mute)
		gpiod_set_value_cansleep(wm8524->mute, mute);

	return 0;
}
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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct cs53l30_private {int /*<<< orphan*/  mute_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct cs53l30_private* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs53l30_mute_stream(struct snd_soc_dai *dai, int mute, int stream)
{
	struct cs53l30_private *priv = snd_soc_component_get_drvdata(dai->component);

	gpiod_set_value_cansleep(priv->mute_gpio, mute);

	return 0;
}
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
struct wm8731_priv {scalar_t__ constraints; } ;
struct snd_soc_dai {int /*<<< orphan*/  component; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct wm8731_priv* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8731_startup(struct snd_pcm_substream *substream,
	struct snd_soc_dai *dai)
{
	struct wm8731_priv *wm8731 = snd_soc_component_get_drvdata(dai->component);

	if (wm8731->constraints)
		snd_pcm_hw_constraint_list(substream->runtime, 0,
					   SNDRV_PCM_HW_PARAM_RATE,
					   wm8731->constraints);

	return 0;
}
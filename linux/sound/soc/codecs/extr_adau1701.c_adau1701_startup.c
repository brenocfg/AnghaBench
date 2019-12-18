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
struct snd_pcm_substream {int dummy; } ;
struct adau1701 {int /*<<< orphan*/  sigmadsp; } ;

/* Variables and functions */
 int sigmadsp_restrict_params (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 struct adau1701* snd_soc_component_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1701_startup(struct snd_pcm_substream *substream,
	struct snd_soc_dai *dai)
{
	struct adau1701 *adau1701 = snd_soc_component_get_drvdata(dai->component);

	return sigmadsp_restrict_params(adau1701->sigmadsp, substream);
}
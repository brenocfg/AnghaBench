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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct adav80x {scalar_t__ rate; } ;

/* Variables and functions */
 struct adav80x* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_is_active (struct snd_soc_component*) ; 

__attribute__((used)) static void adav80x_dai_shutdown(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct adav80x *adav80x = snd_soc_component_get_drvdata(component);

	if (!snd_soc_component_is_active(component))
		adav80x->rate = 0;
}
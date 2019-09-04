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
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  twl4030_voice_enable (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl4030_voice_shutdown(struct snd_pcm_substream *substream,
				   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;

	/* Enable voice digital filters */
	twl4030_voice_enable(component, substream->stream, 0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct twl4030_priv {scalar_t__ configured; struct snd_pcm_substream* master_substream; struct snd_pcm_substream* slave_substream; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; TYPE_1__* runtime; } ;
struct TYPE_2__ {int channels; } ;

/* Variables and functions */
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  twl4030_tdm_enable (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl4030_shutdown(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	if (twl4030->master_substream == substream)
		twl4030->master_substream = twl4030->slave_substream;

	twl4030->slave_substream = NULL;

	/* If all streams are closed, or the remaining stream has not yet
	 * been configured than set the DAI as not configured. */
	if (!twl4030->master_substream)
		twl4030->configured = 0;
	 else if (!twl4030->master_substream->runtime->channels)
		twl4030->configured = 0;

	 /* If the closing substream had 4 channel, do the necessary cleanup */
	if (substream->runtime->channels == 4)
		twl4030_tdm_enable(component, substream->stream, 0);
}
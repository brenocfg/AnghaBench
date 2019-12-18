#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_route {char* sink; int /*<<< orphan*/  source; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_dai {struct hdmi_codec_daifmt* playback_dma_data; int /*<<< orphan*/  component; TYPE_2__* driver; } ;
struct hdmi_codec_daifmt {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream_name; } ;
struct TYPE_4__ {TYPE_1__ playback; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hdmi_codec_daifmt* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,struct snd_soc_dapm_route*,int) ; 

__attribute__((used)) static int hdmi_dai_probe(struct snd_soc_dai *dai)
{
	struct snd_soc_dapm_context *dapm;
	struct hdmi_codec_daifmt *daifmt;
	struct snd_soc_dapm_route route = {
		.sink = "TX",
		.source = dai->driver->playback.stream_name,
	};
	int ret;

	dapm = snd_soc_component_get_dapm(dai->component);
	ret = snd_soc_dapm_add_routes(dapm, &route, 1);
	if (ret)
		return ret;

	daifmt = kzalloc(sizeof(*daifmt), GFP_KERNEL);
	if (!daifmt)
		return -ENOMEM;

	dai->playback_dma_data = daifmt;
	return 0;
}
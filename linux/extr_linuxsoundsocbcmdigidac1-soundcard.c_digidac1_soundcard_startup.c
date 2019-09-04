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
struct snd_soc_pcm_runtime {TYPE_2__* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; TYPE_1__* dai_link; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_4__ {struct snd_soc_component* component; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  WM8741_DACLLSB_ATTENUATION ; 
 int /*<<< orphan*/  WM8741_DACLMSB_ATTENUATION ; 
 int /*<<< orphan*/  WM8741_DACRLSB_ATTENUATION ; 
 int /*<<< orphan*/  WM8741_DACRMSB_ATTENUATION ; 
 int WM8741_UPDATELL ; 
 int WM8741_UPDATELM ; 
 int WM8741_UPDATERL ; 
 int WM8741_UPDATERM ; 
 int /*<<< orphan*/  WM8804_PWRDN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digidac1_soundcard_startup(struct snd_pcm_substream *substream)
{
	/* turn on wm8804 digital output */
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = rtd->codec_dai->component;
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_pcm_runtime *wm8741_rtd;
	struct snd_soc_component *wm8741_component;

	snd_soc_component_update_bits(component, WM8804_PWRDN, 0x3c, 0x00);
	wm8741_rtd = snd_soc_get_pcm_runtime(card, card->dai_link[1].name);
	if (!wm8741_rtd) {
		dev_warn(card->dev, "digidac1_soundcard_startup: couldn't get WM8741 rtd\n");
		return -EFAULT;
	}
	wm8741_component = wm8741_rtd->codec_dai->component;

	/* latch wm8741 level */
	snd_soc_component_update_bits(wm8741_component, WM8741_DACLLSB_ATTENUATION,
		WM8741_UPDATELL, WM8741_UPDATELL);
	snd_soc_component_update_bits(wm8741_component, WM8741_DACLMSB_ATTENUATION,
		WM8741_UPDATELM, WM8741_UPDATELM);
	snd_soc_component_update_bits(wm8741_component, WM8741_DACRLSB_ATTENUATION,
		WM8741_UPDATERL, WM8741_UPDATERL);
	snd_soc_component_update_bits(wm8741_component, WM8741_DACRMSB_ATTENUATION,
		WM8741_UPDATERM, WM8741_UPDATERM);

	return 0;
}
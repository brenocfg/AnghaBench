#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_2__* codec_dai; struct snd_soc_card* card; } ;
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; TYPE_1__* dai_link; struct snd_card* snd_card; } ;
struct snd_kcontrol {TYPE_3__* vd; } ;
struct snd_card {int dummy; } ;
struct TYPE_6__ {void* access; } ;
struct TYPE_5__ {struct snd_soc_component* component; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EFAULT ; 
 void* SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  WM8804_PWRDN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snd_ctl_remove (struct snd_card*,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_soc_card_get_kcontrol (struct snd_soc_card*,char*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 
 int w8741_add_controls (struct snd_soc_component*) ; 

__attribute__((used)) static int digidac1_soundcard_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_pcm_runtime *wm8741_rtd;
	struct snd_soc_component *wm8741_component;
	struct snd_card *sound_card = card->snd_card;
	struct snd_kcontrol *kctl;
	int ret;

	wm8741_rtd = snd_soc_get_pcm_runtime(card, card->dai_link[1].name);
	if (!wm8741_rtd) {
		dev_warn(card->dev, "digidac1_soundcard_init: couldn't get wm8741 rtd\n");
		return -EFAULT;
	}
	wm8741_component = wm8741_rtd->codec_dai->component;
	ret = w8741_add_controls(wm8741_component);
	if (ret < 0)
		dev_warn(card->dev, "Failed to add new wm8741 controls: %d\n",
		ret);

	/* enable TX output */
	snd_soc_component_update_bits(component, WM8804_PWRDN, 0x4, 0x0);

	kctl = snd_soc_card_get_kcontrol(card,
		"Playback Volume");
	if (kctl) {
		kctl->vd[0].access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
		snd_ctl_remove(sound_card, kctl);
		}
	kctl = snd_soc_card_get_kcontrol(card,
		"Fine Playback Volume");
	if (kctl) {
		kctl->vd[0].access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
		snd_ctl_remove(sound_card, kctl);
		}
	return 0;
}
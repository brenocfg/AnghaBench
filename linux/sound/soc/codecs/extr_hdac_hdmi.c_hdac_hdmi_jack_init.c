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
struct snd_soc_jack {int dummy; } ;
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  card; } ;
struct snd_pcm {int dummy; } ;
struct hdac_hdmi_priv {int /*<<< orphan*/  pcm_list; int /*<<< orphan*/  chmap; TYPE_1__* dai_map; struct hdac_device* hdev; } ;
struct hdac_hdmi_pcm {int pcm_id; int /*<<< orphan*/  head; int /*<<< orphan*/  port_list; int /*<<< orphan*/  lock; struct snd_soc_jack* jack; scalar_t__ jack_event; int /*<<< orphan*/  cvt; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cvt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 struct hdac_hdmi_pcm* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct snd_pcm* hdac_hdmi_get_pcm_from_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_hdac_add_chmap_ctls (struct snd_pcm*,int,int /*<<< orphan*/ *) ; 
 struct hdac_hdmi_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int hdac_hdmi_jack_init(struct snd_soc_dai *dai, int device,
				struct snd_soc_jack *jack)
{
	struct snd_soc_component *component = dai->component;
	struct hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	struct hdac_device *hdev = hdmi->hdev;
	struct hdac_hdmi_pcm *pcm;
	struct snd_pcm *snd_pcm;
	int err;

	/*
	 * this is a new PCM device, create new pcm and
	 * add to the pcm list
	 */
	pcm = devm_kzalloc(&hdev->dev, sizeof(*pcm), GFP_KERNEL);
	if (!pcm)
		return -ENOMEM;
	pcm->pcm_id = device;
	pcm->cvt = hdmi->dai_map[dai->id].cvt;
	pcm->jack_event = 0;
	pcm->jack = jack;
	mutex_init(&pcm->lock);
	INIT_LIST_HEAD(&pcm->port_list);
	snd_pcm = hdac_hdmi_get_pcm_from_id(dai->component->card, device);
	if (snd_pcm) {
		err = snd_hdac_add_chmap_ctls(snd_pcm, device, &hdmi->chmap);
		if (err < 0) {
			dev_err(&hdev->dev,
				"chmap control add failed with err: %d for pcm: %d\n",
				err, device);
			return err;
		}
	}

	list_add_tail(&pcm->head, &hdmi->pcm_list);

	return 0;
}
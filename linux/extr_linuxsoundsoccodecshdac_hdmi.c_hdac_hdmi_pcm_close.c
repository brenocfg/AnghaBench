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
struct snd_soc_dai {size_t id; } ;
struct snd_pcm_substream {int dummy; } ;
struct hdac_hdmi_priv {struct hdac_hdmi_dai_port_map* dai_map; } ;
struct hdac_hdmi_pcm {int chmap_set; int /*<<< orphan*/  lock; scalar_t__ channels; int /*<<< orphan*/  chmap; } ;
struct hdac_hdmi_dai_port_map {int /*<<< orphan*/ * port; int /*<<< orphan*/  cvt; } ;

/* Variables and functions */
 struct hdac_hdmi_pcm* hdac_hdmi_get_pcm_from_cvt (struct hdac_hdmi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hdac_hdmi_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void hdac_hdmi_pcm_close(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	struct hdac_hdmi_priv *hdmi = snd_soc_dai_get_drvdata(dai);
	struct hdac_hdmi_dai_port_map *dai_map;
	struct hdac_hdmi_pcm *pcm;

	dai_map = &hdmi->dai_map[dai->id];

	pcm = hdac_hdmi_get_pcm_from_cvt(hdmi, dai_map->cvt);

	if (pcm) {
		mutex_lock(&pcm->lock);
		pcm->chmap_set = false;
		memset(pcm->chmap, 0, sizeof(pcm->chmap));
		pcm->channels = 0;
		mutex_unlock(&pcm->lock);
	}

	if (dai_map->port)
		dai_map->port = NULL;
}
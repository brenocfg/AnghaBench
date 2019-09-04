#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {size_t id; TYPE_4__* driver; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct hdac_hdmi_priv {struct hdac_hdmi_dai_port_map* dai_map; struct hdac_device* hdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  eld_valid; int /*<<< orphan*/  monitor_present; } ;
struct hdac_hdmi_port {int /*<<< orphan*/  id; TYPE_2__* pin; TYPE_1__ eld; } ;
struct hdac_hdmi_pcm {int format; int /*<<< orphan*/  channels; } ;
struct hdac_hdmi_dai_port_map {int /*<<< orphan*/  cvt; struct hdac_hdmi_port* port; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  sig_bits; } ;
struct TYPE_8__ {TYPE_3__ playback; } ;
struct TYPE_6__ {int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdac_hdmi_pcm* hdac_hdmi_get_pcm_from_cvt (struct hdac_hdmi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int snd_hdac_calc_stream_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdac_hdmi_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int hdac_hdmi_set_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *hparams, struct snd_soc_dai *dai)
{
	struct hdac_hdmi_priv *hdmi = snd_soc_dai_get_drvdata(dai);
	struct hdac_device *hdev = hdmi->hdev;
	struct hdac_hdmi_dai_port_map *dai_map;
	struct hdac_hdmi_port *port;
	struct hdac_hdmi_pcm *pcm;
	int format;

	dai_map = &hdmi->dai_map[dai->id];
	port = dai_map->port;

	if (!port)
		return -ENODEV;

	if ((!port->eld.monitor_present) || (!port->eld.eld_valid)) {
		dev_err(&hdev->dev,
			"device is not configured for this pin:port%d:%d\n",
					port->pin->nid, port->id);
		return -ENODEV;
	}

	format = snd_hdac_calc_stream_format(params_rate(hparams),
			params_channels(hparams), params_format(hparams),
			dai->driver->playback.sig_bits, 0);

	pcm = hdac_hdmi_get_pcm_from_cvt(hdmi, dai_map->cvt);
	if (!pcm)
		return -EIO;

	pcm->format = format;
	pcm->channels = params_channels(hparams);

	return 0;
}
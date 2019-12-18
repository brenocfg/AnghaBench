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
struct snd_soc_dai {size_t id; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct hdac_hdmi_priv {struct hdac_hdmi_dai_port_map* dai_map; struct hdac_device* hdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  eld_buffer; int /*<<< orphan*/  eld_valid; int /*<<< orphan*/  monitor_present; } ;
struct hdac_hdmi_port {TYPE_2__ eld; int /*<<< orphan*/  id; TYPE_1__* pin; } ;
struct hdac_hdmi_dai_port_map {struct hdac_hdmi_port* port; struct hdac_hdmi_cvt* cvt; } ;
struct hdac_hdmi_cvt {int dummy; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdac_hdmi_eld_limit_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdac_hdmi_port* hdac_hdmi_get_port_from_cvt (struct hdac_device*,struct hdac_hdmi_priv*,struct hdac_hdmi_cvt*) ; 
 int snd_pcm_hw_constraint_eld (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdac_hdmi_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int hdac_hdmi_pcm_open(struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	struct hdac_hdmi_priv *hdmi = snd_soc_dai_get_drvdata(dai);
	struct hdac_device *hdev = hdmi->hdev;
	struct hdac_hdmi_dai_port_map *dai_map;
	struct hdac_hdmi_cvt *cvt;
	struct hdac_hdmi_port *port;
	int ret;

	dai_map = &hdmi->dai_map[dai->id];

	cvt = dai_map->cvt;
	port = hdac_hdmi_get_port_from_cvt(hdev, hdmi, cvt);

	/*
	 * To make PA and other userland happy.
	 * userland scans devices so returning error does not help.
	 */
	if (!port)
		return 0;
	if ((!port->eld.monitor_present) ||
			(!port->eld.eld_valid)) {

		dev_warn(&hdev->dev,
			"Failed: present?:%d ELD valid?:%d pin:port: %d:%d\n",
			port->eld.monitor_present, port->eld.eld_valid,
			port->pin->nid, port->id);

		return 0;
	}

	dai_map->port = port;

	ret = hdac_hdmi_eld_limit_formats(substream->runtime,
				port->eld.eld_buffer);
	if (ret < 0)
		return ret;

	return snd_pcm_hw_constraint_eld(substream->runtime,
				port->eld.eld_buffer);
}
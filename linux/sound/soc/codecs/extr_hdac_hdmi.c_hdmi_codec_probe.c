#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dapm_context {TYPE_1__* card; } ;
struct snd_soc_component {TYPE_2__* card; } ;
struct hdac_hdmi_priv {int /*<<< orphan*/  card; struct snd_soc_component* component; struct hdac_device* hdev; } ;
struct hdac_ext_link {int dummy; } ;
struct hdac_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct TYPE_7__ {struct hdac_device* audio_ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  snd_card; } ;

/* Variables and functions */
 int DL_FLAG_AUTOREMOVE_CONSUMER ; 
 int DL_FLAG_RPM_ACTIVE ; 
 int EIO ; 
 TYPE_3__ aops ; 
 int create_fill_widget_route_map (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_link_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdac_hdmi_present_sense_all_pins (struct hdac_device*,struct hdac_hdmi_priv*,int) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspend (int /*<<< orphan*/ *) ; 
 int snd_hdac_acomp_register_notifier (int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct hdac_ext_link* snd_hdac_ext_bus_get_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_link_get (int /*<<< orphan*/ ,struct hdac_ext_link*) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct hdac_hdmi_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int hdmi_codec_probe(struct snd_soc_component *component)
{
	struct hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	struct hdac_device *hdev = hdmi->hdev;
	struct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	struct hdac_ext_link *hlink = NULL;
	int ret;

	hdmi->component = component;

	/*
	 * hold the ref while we probe, also no need to drop the ref on
	 * exit, we call pm_runtime_suspend() so that will do for us
	 */
	hlink = snd_hdac_ext_bus_get_link(hdev->bus, dev_name(&hdev->dev));
	if (!hlink) {
		dev_err(&hdev->dev, "hdac link not found\n");
		return -EIO;
	}

	snd_hdac_ext_bus_link_get(hdev->bus, hlink);

	ret = create_fill_widget_route_map(dapm);
	if (ret < 0)
		return ret;

	aops.audio_ptr = hdev;
	ret = snd_hdac_acomp_register_notifier(hdev->bus, &aops);
	if (ret < 0) {
		dev_err(&hdev->dev, "notifier register failed: err: %d\n", ret);
		return ret;
	}

	hdac_hdmi_present_sense_all_pins(hdev, hdmi, true);
	/* Imp: Store the card pointer in hda_codec */
	hdmi->card = dapm->card->snd_card;

	/*
	 * Setup a device_link between card device and HDMI codec device.
	 * The card device is the consumer and the HDMI codec device is
	 * the supplier. With this setting, we can make sure that the audio
	 * domain in display power will be always turned on before operating
	 * on the HDMI audio codec registers.
	 * Let's use the flag DL_FLAG_AUTOREMOVE_CONSUMER. This can make
	 * sure the device link is freed when the machine driver is removed.
	 */
	device_link_add(component->card->dev, &hdev->dev, DL_FLAG_RPM_ACTIVE |
			DL_FLAG_AUTOREMOVE_CONSUMER);
	/*
	 * hdac_device core already sets the state to active and calls
	 * get_noresume. So enable runtime and set the device to suspend.
	 */
	pm_runtime_enable(&hdev->dev);
	pm_runtime_put(&hdev->dev);
	pm_runtime_suspend(&hdev->dev);

	return 0;
}
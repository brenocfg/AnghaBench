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
struct snd_soc_component {int dummy; } ;
struct hdac_hdmi_priv {struct hdac_device* hdev; } ;
struct hdac_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int snd_hdac_acomp_register_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hdac_hdmi_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void hdmi_codec_remove(struct snd_soc_component *component)
{
	struct hdac_hdmi_priv *hdmi = snd_soc_component_get_drvdata(component);
	struct hdac_device *hdev = hdmi->hdev;
	int ret;

	ret = snd_hdac_acomp_register_notifier(hdev->bus, NULL);
	if (ret < 0)
		dev_err(&hdev->dev, "notifier unregister failed: err: %d\n",
				ret);

	pm_runtime_disable(&hdev->dev);
}
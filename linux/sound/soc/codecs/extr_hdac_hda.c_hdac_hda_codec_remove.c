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
struct snd_soc_component {int dummy; } ;
struct hdac_device {int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct hdac_device core; } ;
struct hdac_hda_priv {TYPE_1__ codec; } ;
struct hdac_ext_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct hdac_ext_link* snd_hdac_ext_bus_get_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_link_put (int /*<<< orphan*/ ,struct hdac_ext_link*) ; 
 struct hdac_hda_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void hdac_hda_codec_remove(struct snd_soc_component *component)
{
	struct hdac_hda_priv *hda_pvt =
		      snd_soc_component_get_drvdata(component);
	struct hdac_device *hdev = &hda_pvt->codec.core;
	struct hdac_ext_link *hlink = NULL;

	hlink = snd_hdac_ext_bus_get_link(hdev->bus, dev_name(&hdev->dev));
	if (!hlink) {
		dev_err(&hdev->dev, "hdac link not found\n");
		return;
	}

	pm_runtime_disable(&hdev->dev);
	snd_hdac_ext_bus_link_put(hdev->bus, hlink);
}
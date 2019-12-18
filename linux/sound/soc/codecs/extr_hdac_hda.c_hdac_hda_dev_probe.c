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
struct hdac_hda_priv {int dummy; } ;
struct hdac_ext_link {int dummy; } ;
struct hdac_device {int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct hdac_hda_priv*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdac_hda_codec ; 
 int /*<<< orphan*/  hdac_hda_dais ; 
 struct hdac_hda_priv* hdac_to_hda_priv (struct hdac_device*) ; 
 struct hdac_ext_link* snd_hdac_ext_bus_get_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_link_get (int /*<<< orphan*/ ,struct hdac_ext_link*) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_link_put (int /*<<< orphan*/ ,struct hdac_ext_link*) ; 

__attribute__((used)) static int hdac_hda_dev_probe(struct hdac_device *hdev)
{
	struct hdac_ext_link *hlink;
	struct hdac_hda_priv *hda_pvt;
	int ret;

	/* hold the ref while we probe */
	hlink = snd_hdac_ext_bus_get_link(hdev->bus, dev_name(&hdev->dev));
	if (!hlink) {
		dev_err(&hdev->dev, "hdac link not found\n");
		return -EIO;
	}
	snd_hdac_ext_bus_link_get(hdev->bus, hlink);

	hda_pvt = hdac_to_hda_priv(hdev);
	if (!hda_pvt)
		return -ENOMEM;

	/* ASoC specific initialization */
	ret = devm_snd_soc_register_component(&hdev->dev,
					 &hdac_hda_codec, hdac_hda_dais,
					 ARRAY_SIZE(hdac_hda_dais));
	if (ret < 0) {
		dev_err(&hdev->dev, "failed to register HDA codec %d\n", ret);
		return ret;
	}

	dev_set_drvdata(&hdev->dev, hda_pvt);
	snd_hdac_ext_bus_link_put(hdev->bus, hlink);

	return ret;
}
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
struct device {int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/  parent; } ;
struct hdac_device {unsigned int addr; int vendor_id; int subsystem_id; struct device dev; int /*<<< orphan*/  chip_name; void* power_caps; scalar_t__ mfg; scalar_t__ afg; void* revision_id; int /*<<< orphan*/  in_pm; int /*<<< orphan*/  widget_lock; int /*<<< orphan*/  type; struct hdac_bus* bus; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 scalar_t__ AC_NODE_ROOT ; 
 int /*<<< orphan*/  AC_PAR_POWER_STATE ; 
 int /*<<< orphan*/  AC_PAR_REV_ID ; 
 int /*<<< orphan*/  AC_PAR_SUBSYSTEM_ID ; 
 int /*<<< orphan*/  AC_PAR_VENDOR_ID ; 
 int /*<<< orphan*/  AC_VERB_GET_SUBSYSTEM_ID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDA_DEV_CORE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_release ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  device_enable_async_suspend (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int get_codec_vendor_name (struct hdac_device*) ; 
 int /*<<< orphan*/  hdac_dev_attr_groups ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  setup_fg_nodes (struct hdac_device*) ; 
 int /*<<< orphan*/  snd_hda_bus_type ; 
 int snd_hdac_bus_add_device (struct hdac_bus*,struct hdac_device*) ; 
 int /*<<< orphan*/  snd_hdac_read (struct hdac_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 void* snd_hdac_read_parm (struct hdac_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int snd_hdac_refresh_widgets (struct hdac_device*) ; 

int snd_hdac_device_init(struct hdac_device *codec, struct hdac_bus *bus,
			 const char *name, unsigned int addr)
{
	struct device *dev;
	hda_nid_t fg;
	int err;

	dev = &codec->dev;
	device_initialize(dev);
	dev->parent = bus->dev;
	dev->bus = &snd_hda_bus_type;
	dev->release = default_release;
	dev->groups = hdac_dev_attr_groups;
	dev_set_name(dev, "%s", name);
	device_enable_async_suspend(dev);

	codec->bus = bus;
	codec->addr = addr;
	codec->type = HDA_DEV_CORE;
	mutex_init(&codec->widget_lock);
	pm_runtime_set_active(&codec->dev);
	pm_runtime_get_noresume(&codec->dev);
	atomic_set(&codec->in_pm, 0);

	err = snd_hdac_bus_add_device(bus, codec);
	if (err < 0)
		goto error;

	/* fill parameters */
	codec->vendor_id = snd_hdac_read_parm(codec, AC_NODE_ROOT,
					      AC_PAR_VENDOR_ID);
	if (codec->vendor_id == -1) {
		/* read again, hopefully the access method was corrected
		 * in the last read...
		 */
		codec->vendor_id = snd_hdac_read_parm(codec, AC_NODE_ROOT,
						      AC_PAR_VENDOR_ID);
	}

	codec->subsystem_id = snd_hdac_read_parm(codec, AC_NODE_ROOT,
						 AC_PAR_SUBSYSTEM_ID);
	codec->revision_id = snd_hdac_read_parm(codec, AC_NODE_ROOT,
						AC_PAR_REV_ID);

	setup_fg_nodes(codec);
	if (!codec->afg && !codec->mfg) {
		dev_err(dev, "no AFG or MFG node found\n");
		err = -ENODEV;
		goto error;
	}

	fg = codec->afg ? codec->afg : codec->mfg;

	err = snd_hdac_refresh_widgets(codec);
	if (err < 0)
		goto error;

	codec->power_caps = snd_hdac_read_parm(codec, fg, AC_PAR_POWER_STATE);
	/* reread ssid if not set by parameter */
	if (codec->subsystem_id == -1 || codec->subsystem_id == 0)
		snd_hdac_read(codec, fg, AC_VERB_GET_SUBSYSTEM_ID, 0,
			      &codec->subsystem_id);

	err = get_codec_vendor_name(codec);
	if (err < 0)
		goto error;

	codec->chip_name = kasprintf(GFP_KERNEL, "ID %x",
				     codec->vendor_id & 0xffff);
	if (!codec->chip_name) {
		err = -ENOMEM;
		goto error;
	}

	return 0;

 error:
	put_device(&codec->dev);
	return err;
}
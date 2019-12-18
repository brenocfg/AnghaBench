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
struct hdac_device {int num_nodes; int /*<<< orphan*/  widget_lock; void* end_nid; void* start_nid; int /*<<< orphan*/  afg; int /*<<< orphan*/  dev; } ;
typedef  void* hda_nid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hda_widget_sysfs_reinit (struct hdac_device*,void*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_hdac_get_sub_nodes (struct hdac_device*,int /*<<< orphan*/ ,void**) ; 

int snd_hdac_refresh_widgets(struct hdac_device *codec)
{
	hda_nid_t start_nid;
	int nums, err = 0;

	/*
	 * Serialize against multiple threads trying to update the sysfs
	 * widgets array.
	 */
	mutex_lock(&codec->widget_lock);
	nums = snd_hdac_get_sub_nodes(codec, codec->afg, &start_nid);
	if (!start_nid || nums <= 0 || nums >= 0xff) {
		dev_err(&codec->dev, "cannot read sub nodes for FG 0x%02x\n",
			codec->afg);
		err = -EINVAL;
		goto unlock;
	}

	err = hda_widget_sysfs_reinit(codec, start_nid, nums);
	if (err < 0)
		goto unlock;

	codec->num_nodes = nums;
	codec->start_nid = start_nid;
	codec->end_nid = start_nid + nums;
unlock:
	mutex_unlock(&codec->widget_lock);
	return err;
}
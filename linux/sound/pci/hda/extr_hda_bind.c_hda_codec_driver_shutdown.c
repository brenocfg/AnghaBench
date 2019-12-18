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
struct TYPE_2__ {int /*<<< orphan*/  (* reboot_notify ) (struct hda_codec*) ;} ;
struct hda_codec {TYPE_1__ patch_ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hda_codec* dev_to_hda_codec (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static void hda_codec_driver_shutdown(struct device *dev)
{
	struct hda_codec *codec = dev_to_hda_codec(dev);

	if (!pm_runtime_suspended(dev) && codec->patch_ops.reboot_notify)
		codec->patch_ops.reboot_notify(codec);
}
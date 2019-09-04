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
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (struct hda_codec*) ;} ;
struct hda_codec {TYPE_1__ patch_ops; } ;
struct device {TYPE_2__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 struct hda_codec* dev_to_hda_codec (struct device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_cleanup_for_unbind (struct hda_codec*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static int hda_codec_driver_remove(struct device *dev)
{
	struct hda_codec *codec = dev_to_hda_codec(dev);

	if (codec->patch_ops.free)
		codec->patch_ops.free(codec);
	snd_hda_codec_cleanup_for_unbind(codec);
	module_put(dev->driver->owner);
	return 0;
}
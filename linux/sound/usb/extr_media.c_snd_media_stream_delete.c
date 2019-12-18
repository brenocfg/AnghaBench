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
struct snd_usb_substream {struct media_ctl* media_ctl; } ;
struct media_device {int /*<<< orphan*/  devnode; } ;
struct media_ctl {int /*<<< orphan*/  media_entity; int /*<<< orphan*/  intf_devnode; struct media_device* media_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct media_ctl*) ; 
 int /*<<< orphan*/  media_device_unregister_entity (int /*<<< orphan*/ *) ; 
 scalar_t__ media_devnode_is_registered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_devnode_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 

void snd_media_stream_delete(struct snd_usb_substream *subs)
{
	struct media_ctl *mctl = subs->media_ctl;

	if (mctl) {
		struct media_device *mdev;

		mdev = mctl->media_dev;
		if (mdev && media_devnode_is_registered(mdev->devnode)) {
			media_devnode_remove(mctl->intf_devnode);
			media_device_unregister_entity(&mctl->media_entity);
			media_entity_cleanup(&mctl->media_entity);
		}
		kfree(mctl);
		subs->media_ctl = NULL;
	}
}
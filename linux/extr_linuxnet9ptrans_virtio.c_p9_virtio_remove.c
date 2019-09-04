#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct virtio_device {TYPE_2__ dev; TYPE_1__* config; struct virtio_chan* priv; } ;
struct virtio_chan {struct virtio_chan* vc_wq; struct virtio_chan* tag; scalar_t__ inuse; int /*<<< orphan*/  chan_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 TYPE_3__ dev_attr_mount_tag ; 
 int /*<<< orphan*/  dev_emerg (TYPE_2__*,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (struct virtio_chan*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  stub2 (struct virtio_device*) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  virtio_9p_lock ; 

__attribute__((used)) static void p9_virtio_remove(struct virtio_device *vdev)
{
	struct virtio_chan *chan = vdev->priv;
	unsigned long warning_time;

	mutex_lock(&virtio_9p_lock);

	/* Remove self from list so we don't get new users. */
	list_del(&chan->chan_list);
	warning_time = jiffies;

	/* Wait for existing users to close. */
	while (chan->inuse) {
		mutex_unlock(&virtio_9p_lock);
		msleep(250);
		if (time_after(jiffies, warning_time + 10 * HZ)) {
			dev_emerg(&vdev->dev,
				  "p9_virtio_remove: waiting for device in use.\n");
			warning_time = jiffies;
		}
		mutex_lock(&virtio_9p_lock);
	}

	mutex_unlock(&virtio_9p_lock);

	vdev->config->reset(vdev);
	vdev->config->del_vqs(vdev);

	sysfs_remove_file(&(vdev->dev.kobj), &dev_attr_mount_tag.attr);
	kobject_uevent(&(vdev->dev.kobj), KOBJ_CHANGE);
	kfree(chan->tag);
	kfree(chan->vc_wq);
	kfree(chan);

}
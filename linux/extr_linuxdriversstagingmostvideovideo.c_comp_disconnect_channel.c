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
struct most_video_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  list; } ;
struct most_interface {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  comp_unregister_videodev (struct most_video_dev*) ; 
 struct most_video_dev* get_comp_dev (struct most_interface*,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int comp_disconnect_channel(struct most_interface *iface,
				   int channel_idx)
{
	struct most_video_dev *mdev = get_comp_dev(iface, channel_idx);

	if (!mdev) {
		pr_err("no such channel is linked\n");
		return -ENOENT;
	}

	spin_lock_irq(&list_lock);
	list_del(&mdev->list);
	spin_unlock_irq(&list_lock);

	comp_unregister_videodev(mdev);
	v4l2_device_disconnect(&mdev->v4l2_dev);
	v4l2_device_put(&mdev->v4l2_dev);
	return 0;
}
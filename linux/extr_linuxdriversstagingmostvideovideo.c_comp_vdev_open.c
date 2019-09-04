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
struct video_device {int vfl_type; } ;
struct most_video_dev {int /*<<< orphan*/  access_ref; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  ch_idx; int /*<<< orphan*/  iface; } ;
struct file {struct comp_fh* private_data; } ;
struct comp_fh {int /*<<< orphan*/  fh; struct most_video_dev* mdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  VFL_TYPE_GRABBER 128 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  kfree (struct comp_fh*) ; 
 struct comp_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int most_start_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct most_video_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int comp_vdev_open(struct file *filp)
{
	int ret;
	struct video_device *vdev = video_devdata(filp);
	struct most_video_dev *mdev = video_drvdata(filp);
	struct comp_fh *fh;

	switch (vdev->vfl_type) {
	case VFL_TYPE_GRABBER:
		break;
	default:
		return -EINVAL;
	}

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	if (!atomic_inc_and_test(&mdev->access_ref)) {
		v4l2_err(&mdev->v4l2_dev, "too many clients\n");
		ret = -EBUSY;
		goto err_dec;
	}

	fh->mdev = mdev;
	v4l2_fh_init(&fh->fh, vdev);
	filp->private_data = fh;

	v4l2_fh_add(&fh->fh);

	ret = most_start_channel(mdev->iface, mdev->ch_idx, &comp);
	if (ret) {
		v4l2_err(&mdev->v4l2_dev, "most_start_channel() failed\n");
		goto err_rm;
	}

	return 0;

err_rm:
	v4l2_fh_del(&fh->fh);
	v4l2_fh_exit(&fh->fh);

err_dec:
	atomic_dec(&mdev->access_ref);
	kfree(fh);
	return ret;
}
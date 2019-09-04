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
struct video_device {char* name; int /*<<< orphan*/  num; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/ * lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bcm2835_codec_dev {int role; int /*<<< orphan*/  instance; int /*<<< orphan*/  v4l2_dev; struct video_device vfd; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  dev_mutex; int /*<<< orphan*/  num_inst; struct platform_device* pdev; } ;
typedef  enum bcm2835_codec_role { ____Placeholder_bcm2835_codec_role } bcm2835_codec_role ;

/* Variables and functions */
#define  DECODE 130 
 int EINVAL ; 
#define  ENCODE 129 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  ISP 128 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VIDIOC_DECODER_CMD ; 
 int /*<<< orphan*/  VIDIOC_ENCODER_CMD ; 
 int /*<<< orphan*/  VIDIOC_TRY_DECODER_CMD ; 
 int /*<<< orphan*/  VIDIOC_TRY_ENCODER_CMD ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bcm2835_codec_get_supported_fmts (struct bcm2835_codec_dev*) ; 
 struct video_device bcm2835_codec_videodev ; 
 int decode_video_nr ; 
 struct bcm2835_codec_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int encode_video_nr ; 
 int isp_video_nr ; 
 int /*<<< orphan*/  m2m_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * roles ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_disable_ioctl (struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_mmal_finalise (int /*<<< orphan*/ ) ; 
 int vchiq_mmal_init (int /*<<< orphan*/ *) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct bcm2835_codec_dev*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

__attribute__((used)) static int bcm2835_codec_create(struct platform_device *pdev,
				struct bcm2835_codec_dev **new_dev,
				enum bcm2835_codec_role role)
{
	struct bcm2835_codec_dev *dev;
	struct video_device *vfd;
	int video_nr;
	int ret;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->pdev = pdev;

	dev->role = role;

	ret = vchiq_mmal_init(&dev->instance);
	if (ret)
		return ret;

	ret = bcm2835_codec_get_supported_fmts(dev);
	if (ret)
		goto vchiq_finalise;

	ret = v4l2_device_register(&pdev->dev, &dev->v4l2_dev);
	if (ret)
		goto vchiq_finalise;

	atomic_set(&dev->num_inst, 0);
	mutex_init(&dev->dev_mutex);

	dev->vfd = bcm2835_codec_videodev;
	vfd = &dev->vfd;
	vfd->lock = &dev->dev_mutex;
	vfd->v4l2_dev = &dev->v4l2_dev;

	switch (role) {
	case DECODE:
		v4l2_disable_ioctl(vfd, VIDIOC_ENCODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_TRY_ENCODER_CMD);
		video_nr = decode_video_nr;
		break;
	case ENCODE:
		v4l2_disable_ioctl(vfd, VIDIOC_DECODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_TRY_DECODER_CMD);
		video_nr = encode_video_nr;
		break;
	case ISP:
		v4l2_disable_ioctl(vfd, VIDIOC_ENCODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_TRY_ENCODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_DECODER_CMD);
		v4l2_disable_ioctl(vfd, VIDIOC_TRY_DECODER_CMD);
		video_nr = isp_video_nr;
		break;
	default:
		ret = -EINVAL;
		goto unreg_dev;
	}

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, video_nr);
	if (ret) {
		v4l2_err(&dev->v4l2_dev, "Failed to register video device\n");
		goto unreg_dev;
	}

	video_set_drvdata(vfd, dev);
	snprintf(vfd->name, sizeof(vfd->name), "%s",
		 bcm2835_codec_videodev.name);
	v4l2_info(&dev->v4l2_dev, "Device registered as /dev/video%d\n",
		  vfd->num);

	*new_dev = dev;

	dev->m2m_dev = v4l2_m2m_init(&m2m_ops);
	if (IS_ERR(dev->m2m_dev)) {
		v4l2_err(&dev->v4l2_dev, "Failed to init mem2mem device\n");
		ret = PTR_ERR(dev->m2m_dev);
		goto err_m2m;
	}

	v4l2_info(&dev->v4l2_dev, "Loaded V4L2 %s\n",
		  roles[role]);
	return 0;

err_m2m:
	v4l2_m2m_release(dev->m2m_dev);
	video_unregister_device(&dev->vfd);
unreg_dev:
	v4l2_device_unregister(&dev->v4l2_dev);
vchiq_finalise:
	vchiq_mmal_finalise(dev->instance);
	return ret;
}
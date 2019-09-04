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
struct v4l2_encoder_cmd {int cmd; } ;
struct file {int dummy; } ;
struct bcm2835_codec_ctx {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ role; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ENCODE ; 
#define  V4L2_ENC_CMD_START 129 
#define  V4L2_ENC_CMD_STOP 128 
 struct bcm2835_codec_ctx* file2ctx (struct file*) ; 

__attribute__((used)) static int vidioc_try_encoder_cmd(struct file *file, void *priv,
				  struct v4l2_encoder_cmd *cmd)
{
	struct bcm2835_codec_ctx *ctx = file2ctx(file);

	if (ctx->dev->role != ENCODE)
		return -EINVAL;

	switch (cmd->cmd) {
	case V4L2_ENC_CMD_STOP:
		break;

	case V4L2_ENC_CMD_START:
		/* Do we need to do anything here? */
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
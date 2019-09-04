#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_control {int value; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  video_fd; } ;
typedef  TYPE_1__ priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  VIDIOC_S_CTRL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_control*) ; 

__attribute__((used)) static int set_mute(priv_t *priv, int value)
{
    struct v4l2_control control;
    control.id = V4L2_CID_AUDIO_MUTE;
    control.value = value;
    if (v4l2_ioctl(priv->video_fd, VIDIOC_S_CTRL, &control) < 0) {
        MP_ERR(priv, "ioctl set mute failed: %s\n", mp_strerror(errno));
        return 0;
    }
    return 1;
}
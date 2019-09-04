#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_2__ format; int /*<<< orphan*/  video_fd; } ;
typedef  TYPE_1__ priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VIDIOC_G_FMT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int getfmt(priv_t *priv)
{
    int i;

    priv->format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if ((i = v4l2_ioctl(priv->video_fd, VIDIOC_G_FMT, &priv->format)) < 0) {
        MP_ERR(priv, "ioctl get format failed: %s\n",
               mp_strerror(errno));
    }
    return i;
}
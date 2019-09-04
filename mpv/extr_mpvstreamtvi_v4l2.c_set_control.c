#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_queryctrl {int value; int default_value; int minimum; int maximum; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct v4l2_control {int value; int default_value; int minimum; int maximum; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  video_fd; } ;
typedef  TYPE_1__ priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int TVI_CONTROL_FALSE ; 
 int TVI_CONTROL_TRUE ; 
 int /*<<< orphan*/  VIDIOC_QUERYCTRL ; 
 int /*<<< orphan*/  VIDIOC_S_CTRL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_queryctrl*) ; 

__attribute__((used)) static int set_control(priv_t *priv, struct v4l2_control *control, int val_signed) {
    struct v4l2_queryctrl        qctrl;
    qctrl.id = control->id;
    if (v4l2_ioctl(priv->video_fd, VIDIOC_QUERYCTRL, &qctrl) < 0) {
        MP_ERR(priv, "ioctl query control failed: %s\n", mp_strerror(errno));
        return TVI_CONTROL_FALSE;
    }

    if (val_signed) {
        if (control->value < 0) {
            control->value = qctrl.default_value + control->value *
                (qctrl.default_value - qctrl.minimum) / 100;
        } else {
            control->value = qctrl.default_value + control->value *
                (qctrl.maximum - qctrl.default_value) / 100;
        }
    } else {
        if (control->value < 50) {
            control->value = qctrl.default_value + (control->value-50) *
                (qctrl.default_value - qctrl.minimum) / 50;
        } else {
            control->value = qctrl.default_value + (control->value-50) *
                (qctrl.maximum - qctrl.default_value) / 50;
        }
    }


    if (v4l2_ioctl(priv->video_fd, VIDIOC_S_CTRL, control) < 0) {
        MP_ERR(priv, "ioctl set %s %d failed: %s\n",
               qctrl.name, control->value, mp_strerror(errno));
        return TVI_CONTROL_FALSE;
    }
    MP_VERBOSE(priv, "set %s: %d [%d, %d]\n",
     qctrl.name, control->value, qctrl.minimum, qctrl.maximum);

    return TVI_CONTROL_TRUE;
}
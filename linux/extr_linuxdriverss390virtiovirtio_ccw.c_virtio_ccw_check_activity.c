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
struct virtio_ccw_device {int curr_io; TYPE_1__* cdev; int /*<<< orphan*/  wait_q; } ;
typedef  int __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  VIRTIO_CCW_DOING_READ_CONFIG 140 
#define  VIRTIO_CCW_DOING_READ_FEAT 139 
#define  VIRTIO_CCW_DOING_READ_STATUS 138 
#define  VIRTIO_CCW_DOING_READ_VQ_CONF 137 
#define  VIRTIO_CCW_DOING_RESET 136 
#define  VIRTIO_CCW_DOING_SET_CONF_IND 135 
#define  VIRTIO_CCW_DOING_SET_IND 134 
#define  VIRTIO_CCW_DOING_SET_IND_ADAPTER 133 
#define  VIRTIO_CCW_DOING_SET_VIRTIO_REV 132 
#define  VIRTIO_CCW_DOING_SET_VQ 131 
#define  VIRTIO_CCW_DOING_WRITE_CONFIG 130 
#define  VIRTIO_CCW_DOING_WRITE_FEAT 129 
#define  VIRTIO_CCW_DOING_WRITE_STATUS 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtio_ccw_check_activity(struct virtio_ccw_device *vcdev,
				      __u32 activity)
{
	if (vcdev->curr_io & activity) {
		switch (activity) {
		case VIRTIO_CCW_DOING_READ_FEAT:
		case VIRTIO_CCW_DOING_WRITE_FEAT:
		case VIRTIO_CCW_DOING_READ_CONFIG:
		case VIRTIO_CCW_DOING_WRITE_CONFIG:
		case VIRTIO_CCW_DOING_WRITE_STATUS:
		case VIRTIO_CCW_DOING_READ_STATUS:
		case VIRTIO_CCW_DOING_SET_VQ:
		case VIRTIO_CCW_DOING_SET_IND:
		case VIRTIO_CCW_DOING_SET_CONF_IND:
		case VIRTIO_CCW_DOING_RESET:
		case VIRTIO_CCW_DOING_READ_VQ_CONF:
		case VIRTIO_CCW_DOING_SET_IND_ADAPTER:
		case VIRTIO_CCW_DOING_SET_VIRTIO_REV:
			vcdev->curr_io &= ~activity;
			wake_up(&vcdev->wait_q);
			break;
		default:
			/* don't know what to do... */
			dev_warn(&vcdev->cdev->dev,
				 "Suspicious activity '%08x'\n", activity);
			WARN_ON(1);
			break;
		}
	}
}
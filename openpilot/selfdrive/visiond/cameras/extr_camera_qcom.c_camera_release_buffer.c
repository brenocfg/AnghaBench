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
struct TYPE_6__ {int dirty_buf; } ;
struct TYPE_5__ {TYPE_1__* ss; int /*<<< orphan*/  isp_fd; } ;
struct TYPE_4__ {TYPE_3__* qbuf_info; } ;
typedef  TYPE_2__ CameraState ;

/* Variables and functions */
 int /*<<< orphan*/  VIDIOC_MSM_ISP_ENQUEUE_BUF ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void camera_release_buffer(void* cookie, int buf_idx) {
  CameraState *s = cookie;
  // printf("camera_release_buffer %d\n", buf_idx);
  s->ss[0].qbuf_info[buf_idx].dirty_buf = 1;
  ioctl(s->isp_fd, VIDIOC_MSM_ISP_ENQUEUE_BUF, &s->ss[0].qbuf_info[buf_idx]);
}
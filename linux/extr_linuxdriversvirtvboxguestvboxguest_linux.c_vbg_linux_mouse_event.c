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
struct vbg_dev {int /*<<< orphan*/  input; TYPE_1__* mouse_status_req; } ;
struct TYPE_2__ {scalar_t__ pointer_pos_y; scalar_t__ pointer_pos_x; scalar_t__ mouse_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int vbg_req_perform (struct vbg_dev*,TYPE_1__*) ; 

void vbg_linux_mouse_event(struct vbg_dev *gdev)
{
	int rc;

	/* Report events to the kernel input device */
	gdev->mouse_status_req->mouse_features = 0;
	gdev->mouse_status_req->pointer_pos_x = 0;
	gdev->mouse_status_req->pointer_pos_y = 0;
	rc = vbg_req_perform(gdev, gdev->mouse_status_req);
	if (rc >= 0) {
		input_report_abs(gdev->input, ABS_X,
				 gdev->mouse_status_req->pointer_pos_x);
		input_report_abs(gdev->input, ABS_Y,
				 gdev->mouse_status_req->pointer_pos_y);
		input_sync(gdev->input);
	}
}
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
struct usbhs_pkt {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhs_dcp_control_transfer_done (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbhsf_ctrl_stage_end(struct usbhs_pkt *pkt, int *is_done)
{
	usbhs_dcp_control_transfer_done(pkt->pipe);

	*is_done = 1;

	return 0;
}
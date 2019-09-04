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
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLRM ; 
 int /*<<< orphan*/  usbhs_fifo_clear_dcp (struct usbhs_pipe*) ; 
 scalar_t__ usbhs_pipe_is_dcp (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsp_pipectrl_set (struct usbhs_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void usbhs_pipe_clear(struct usbhs_pipe *pipe)
{
	if (usbhs_pipe_is_dcp(pipe)) {
		usbhs_fifo_clear_dcp(pipe);
	} else {
		usbhsp_pipectrl_set(pipe, ACLRM, ACLRM);
		usbhsp_pipectrl_set(pipe, ACLRM, 0);
	}
}
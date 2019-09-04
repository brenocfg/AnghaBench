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
typedef  int /*<<< orphan*/  u16 ;
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBUSY ; 
 int /*<<< orphan*/  PID_MASK ; 
 int /*<<< orphan*/  PID_NAK ; 
 int /*<<< orphan*/  __usbhsp_pid_try_nak_if_stall (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usbhsp_pipectrl_get (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsp_pipectrl_set (struct usbhs_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void usbhs_pipe_disable(struct usbhs_pipe *pipe)
{
	int timeout = 1024;
	u16 val;

	/* see "Pipe n Control Register" - "PID" */
	__usbhsp_pid_try_nak_if_stall(pipe);

	usbhsp_pipectrl_set(pipe, PID_MASK, PID_NAK);

	do {
		val  = usbhsp_pipectrl_get(pipe);
		val &= PBUSY;
		if (!val)
			break;

		udelay(10);
	} while (timeout--);
}
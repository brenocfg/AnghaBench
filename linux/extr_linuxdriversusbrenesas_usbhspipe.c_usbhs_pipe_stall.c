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
typedef  int u16 ;
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
#define  PID_BUF 129 
 int PID_MASK ; 
#define  PID_NAK 128 
 int /*<<< orphan*/  PID_STALL10 ; 
 int /*<<< orphan*/  PID_STALL11 ; 
 int usbhsp_pipectrl_get (struct usbhs_pipe*) ; 
 int /*<<< orphan*/  usbhsp_pipectrl_set (struct usbhs_pipe*,int,int /*<<< orphan*/ ) ; 

void usbhs_pipe_stall(struct usbhs_pipe *pipe)
{
	u16 pid = usbhsp_pipectrl_get(pipe);

	pid &= PID_MASK;

	/*
	 * see
	 * "Pipe n Control Register" - "PID"
	 */
	switch (pid) {
	case PID_NAK:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_STALL10);
		break;
	case PID_BUF:
		usbhsp_pipectrl_set(pipe, PID_MASK, PID_STALL11);
		break;
	}
}
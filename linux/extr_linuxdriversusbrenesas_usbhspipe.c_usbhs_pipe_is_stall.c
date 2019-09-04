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
typedef  scalar_t__ u16 ;
struct usbhs_pipe {int dummy; } ;

/* Variables and functions */
 scalar_t__ PID_MASK ; 
 scalar_t__ PID_STALL10 ; 
 scalar_t__ PID_STALL11 ; 
 scalar_t__ usbhsp_pipectrl_get (struct usbhs_pipe*) ; 

int usbhs_pipe_is_stall(struct usbhs_pipe *pipe)
{
	u16 pid = usbhsp_pipectrl_get(pipe) & PID_MASK;

	return (int)(pid == PID_STALL10 || pid == PID_STALL11);
}
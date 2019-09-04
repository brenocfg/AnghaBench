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
 int /*<<< orphan*/  IS_RUNNING ; 
 int usbhsp_flags_has (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 

int usbhs_pipe_is_running(struct usbhs_pipe *pipe)
{
	return usbhsp_flags_has(pipe, IS_RUNNING);
}
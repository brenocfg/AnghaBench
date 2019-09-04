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
 size_t usbhs_pipe_type (struct usbhs_pipe*) ; 
 char** usbhsp_pipe_name ; 

char *usbhs_pipe_name(struct usbhs_pipe *pipe)
{
	return usbhsp_pipe_name[usbhs_pipe_type(pipe)];
}
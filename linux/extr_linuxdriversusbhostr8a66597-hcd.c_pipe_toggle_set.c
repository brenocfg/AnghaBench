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
struct urb {int /*<<< orphan*/  pipe; } ;
struct r8a66597_pipe {int dummy; } ;
struct r8a66597_device {int dummy; } ;
struct r8a66597 {int dummy; } ;

/* Variables and functions */
 unsigned short* get_toggle_pointer (struct r8a66597_device*,int /*<<< orphan*/ ) ; 
 struct r8a66597_device* get_urb_to_r8a66597_dev (struct r8a66597*,struct urb*) ; 
 unsigned char usb_pipeendpoint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_toggle_set(struct r8a66597 *r8a66597,
			    struct r8a66597_pipe *pipe,
			    struct urb *urb, int set)
{
	struct r8a66597_device *dev = get_urb_to_r8a66597_dev(r8a66597, urb);
	unsigned char endpoint = usb_pipeendpoint(urb->pipe);
	unsigned short *toggle = get_toggle_pointer(dev, urb->pipe);

	if (!toggle)
		return;

	if (set)
		*toggle |= 1 << endpoint;
	else
		*toggle &= ~(1 << endpoint);
}
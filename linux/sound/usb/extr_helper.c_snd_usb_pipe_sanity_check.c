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
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIPE_BULK 131 
#define  PIPE_CONTROL 130 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 
 size_t usb_endpoint_type (int /*<<< orphan*/ *) ; 
 struct usb_host_endpoint* usb_pipe_endpoint (struct usb_device*,unsigned int) ; 
 int const usb_pipetype (unsigned int) ; 

int snd_usb_pipe_sanity_check(struct usb_device *dev, unsigned int pipe)
{
	static const int pipetypes[4] = {
		PIPE_CONTROL, PIPE_ISOCHRONOUS, PIPE_BULK, PIPE_INTERRUPT
	};
	struct usb_host_endpoint *ep;

	ep = usb_pipe_endpoint(dev, pipe);
	if (!ep || usb_pipetype(pipe) != pipetypes[usb_endpoint_type(&ep->desc)])
		return -EINVAL;
	return 0;
}
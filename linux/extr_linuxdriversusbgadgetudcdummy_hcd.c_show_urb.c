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
struct urb {int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  pipe; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int speed; } ;

/* Variables and functions */
#define  PIPE_BULK 134 
#define  PIPE_CONTROL 133 
#define  PIPE_INTERRUPT 132 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_SUPER 128 
 int /*<<< orphan*/  scnprintf (char*,size_t,char*,struct urb*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ssize_t show_urb(char *buf, size_t size, struct urb *urb)
{
	int ep = usb_pipeendpoint(urb->pipe);

	return scnprintf(buf, size,
		"urb/%p %s ep%d%s%s len %d/%d\n",
		urb,
		({ char *s;
		switch (urb->dev->speed) {
		case USB_SPEED_LOW:
			s = "ls";
			break;
		case USB_SPEED_FULL:
			s = "fs";
			break;
		case USB_SPEED_HIGH:
			s = "hs";
			break;
		case USB_SPEED_SUPER:
			s = "ss";
			break;
		default:
			s = "?";
			break;
		 } s; }),
		ep, ep ? (usb_pipein(urb->pipe) ? "in" : "out") : "",
		({ char *s; \
		switch (usb_pipetype(urb->pipe)) { \
		case PIPE_CONTROL: \
			s = ""; \
			break; \
		case PIPE_BULK: \
			s = "-bulk"; \
			break; \
		case PIPE_INTERRUPT: \
			s = "-int"; \
			break; \
		default: \
			s = "-iso"; \
			break; \
		} s; }),
		urb->actual_length, urb->transfer_buffer_length);
}
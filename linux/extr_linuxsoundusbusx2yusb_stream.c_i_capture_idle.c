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
struct usb_stream_kernel {int /*<<< orphan*/  i_urb; } ;
struct urb {struct usb_stream_kernel* context; } ;

/* Variables and functions */
 scalar_t__ balance_capture (struct usb_stream_kernel*,struct urb*) ; 
 int /*<<< orphan*/  stream_idle (struct usb_stream_kernel*,struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i_capture_idle(struct urb *urb)
{
	struct usb_stream_kernel *sk = urb->context;
	if (balance_capture(sk, urb))
		stream_idle(sk, urb, sk->i_urb);
}
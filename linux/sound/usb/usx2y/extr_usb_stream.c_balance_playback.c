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
struct usb_stream_kernel {int /*<<< orphan*/  iso_frame_balance; } ;
struct urb {scalar_t__ number_of_packets; } ;

/* Variables and functions */
 int balance_check (struct usb_stream_kernel*,struct urb*) ; 

__attribute__((used)) static bool balance_playback(struct usb_stream_kernel *sk, struct urb *urb)
{
	sk->iso_frame_balance += urb->number_of_packets;
	return balance_check(sk, urb);
}
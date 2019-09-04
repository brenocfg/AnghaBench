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
struct usb_iso_packet_descriptor {int dummy; } ;
struct urb {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct urb* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_init_urb (struct urb*) ; 

struct urb *usb_alloc_urb(int iso_packets, gfp_t mem_flags)
{
	struct urb *urb;

	urb = kmalloc(sizeof(struct urb) +
		iso_packets * sizeof(struct usb_iso_packet_descriptor),
		mem_flags);
	if (!urb)
		return NULL;
	usb_init_urb(urb);
	return urb;
}
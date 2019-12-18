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
struct urb {void (* complete ) (struct urb*) ;} ;

/* Variables and functions */
 int USB_STREAM_NURBS ; 

__attribute__((used)) static void subs_set_complete(struct urb **urbs, void (*complete)(struct urb *))
{
	int u;

	for (u = 0; u < USB_STREAM_NURBS; u++) {
		struct urb *urb = urbs[u];
		urb->complete = complete;
	}
}
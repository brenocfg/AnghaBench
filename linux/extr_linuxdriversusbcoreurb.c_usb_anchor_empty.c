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
struct usb_anchor {int /*<<< orphan*/  urb_list; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 

int usb_anchor_empty(struct usb_anchor *anchor)
{
	return list_empty(&anchor->urb_list);
}
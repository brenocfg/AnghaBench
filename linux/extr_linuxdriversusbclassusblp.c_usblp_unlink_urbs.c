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
struct usblp {int /*<<< orphan*/  urbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usblp_unlink_urbs(struct usblp *usblp)
{
	usb_kill_anchored_urbs(&usblp->urbs);
}
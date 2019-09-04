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
struct usb_composite_dev {int /*<<< orphan*/  gstrings; int /*<<< orphan*/  configs; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void composite_init_dev(struct usb_composite_dev *cdev)
{
	spin_lock_init(&cdev->lock);
	INIT_LIST_HEAD(&cdev->configs);
	INIT_LIST_HEAD(&cdev->gstrings);
}
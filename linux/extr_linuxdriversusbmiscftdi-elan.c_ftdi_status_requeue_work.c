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
struct usb_ftdi {int /*<<< orphan*/  kref; int /*<<< orphan*/  status_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftdi_elan_delete ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void ftdi_status_requeue_work(struct usb_ftdi *ftdi, unsigned int delta)
{
	if (!schedule_delayed_work(&ftdi->status_work, delta))
		kref_put(&ftdi->kref, ftdi_elan_delete);
}
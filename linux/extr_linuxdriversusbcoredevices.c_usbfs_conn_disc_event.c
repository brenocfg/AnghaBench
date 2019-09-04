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
struct TYPE_2__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 TYPE_1__ device_event ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void usbfs_conn_disc_event(void)
{
	atomic_add(2, &device_event.count);
	wake_up(&device_event.wait);
}
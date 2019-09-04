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
struct usb_serial {int num_ports; scalar_t__ minors_reserved; TYPE_1__** port; } ;
struct TYPE_2__ {int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_minors ; 
 int /*<<< orphan*/  table_lock ; 

__attribute__((used)) static void release_minors(struct usb_serial *serial)
{
	int i;

	mutex_lock(&table_lock);
	for (i = 0; i < serial->num_ports; ++i)
		idr_remove(&serial_minors, serial->port[i]->minor);
	mutex_unlock(&table_lock);
	serial->minors_reserved = 0;
}
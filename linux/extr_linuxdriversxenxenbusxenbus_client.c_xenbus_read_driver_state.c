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
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int /*<<< orphan*/  XBT_NIL ; 
 int XenbusStateUnknown ; 
 int xenbus_gather (int /*<<< orphan*/ ,char const*,char*,char*,int*,int /*<<< orphan*/ *) ; 

enum xenbus_state xenbus_read_driver_state(const char *path)
{
	enum xenbus_state result;
	int err = xenbus_gather(XBT_NIL, path, "state", "%d", &result, NULL);
	if (err)
		result = XenbusStateUnknown;

	return result;
}
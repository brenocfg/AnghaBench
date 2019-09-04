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
struct hid_device {struct gb_hid* driver_data; } ;
struct gb_hid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_hid_free_buffers (struct gb_hid*) ; 

__attribute__((used)) static void gb_hid_stop(struct hid_device *hid)
{
	struct gb_hid *ghid = hid->driver_data;

	gb_hid_free_buffers(ghid);
}
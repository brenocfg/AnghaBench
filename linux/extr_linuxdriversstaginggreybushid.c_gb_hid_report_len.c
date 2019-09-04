#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hid_report {int size; size_t type; TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_1__* report_enum; } ;
struct TYPE_3__ {int numbered; } ;

/* Variables and functions */

__attribute__((used)) static int gb_hid_report_len(struct hid_report *report)
{
	return ((report->size - 1) >> 3) + 1 +
		report->device->report_enum[report->type].numbered;
}
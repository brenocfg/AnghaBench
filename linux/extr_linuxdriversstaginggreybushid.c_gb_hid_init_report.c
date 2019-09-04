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
struct hid_report {int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct gb_hid {int /*<<< orphan*/  inbuf; int /*<<< orphan*/  hid; } ;

/* Variables and functions */
 scalar_t__ gb_hid_get_report (struct gb_hid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int gb_hid_report_len (struct hid_report*) ; 
 int /*<<< orphan*/  hid_report_raw_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void gb_hid_init_report(struct gb_hid *ghid, struct hid_report *report)
{
	unsigned int size;

	size = gb_hid_report_len(report);
	if (gb_hid_get_report(ghid, report->type, report->id, ghid->inbuf,
			      size))
		return;

	/*
	 * hid->driver_lock is held as we are in probe function,
	 * we just need to setup the input fields, so using
	 * hid_report_raw_event is safe.
	 */
	hid_report_raw_event(ghid->hid, report->type, ghid->inbuf, size, 1);
}
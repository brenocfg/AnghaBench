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
struct hidp_session {int /*<<< orphan*/  rd_size; int /*<<< orphan*/  rd_data; int /*<<< orphan*/  hid; } ;
struct hid_device {struct hidp_session* driver_data; } ;

/* Variables and functions */
 int hid_parse_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidp_parse(struct hid_device *hid)
{
	struct hidp_session *session = hid->driver_data;

	return hid_parse_report(session->hid, session->rd_data,
			session->rd_size);
}
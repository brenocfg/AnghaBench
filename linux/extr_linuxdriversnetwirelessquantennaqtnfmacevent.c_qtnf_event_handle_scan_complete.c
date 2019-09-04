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
typedef  int u16 ;
struct qtnf_wmac {int /*<<< orphan*/  macid; } ;
struct qlink_event_scan_complete {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int QLINK_SCAN_ABORTED ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_scan_done (struct qtnf_wmac*,int) ; 

__attribute__((used)) static int
qtnf_event_handle_scan_complete(struct qtnf_wmac *mac,
				const struct qlink_event_scan_complete *status,
				u16 len)
{
	if (len < sizeof(*status)) {
		pr_err("MAC%u: payload is too short\n", mac->macid);
		return -EINVAL;
	}

	qtnf_scan_done(mac, le32_to_cpu(status->flags) & QLINK_SCAN_ABORTED);

	return 0;
}
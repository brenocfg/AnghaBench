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
struct hci_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_req_add_le_scan_disable (struct hci_request*) ; 

__attribute__((used)) static int le_scan_disable(struct hci_request *req, unsigned long opt)
{
	hci_req_add_le_scan_disable(req);
	return 0;
}
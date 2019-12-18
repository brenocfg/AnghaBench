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
struct hci_request {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_dev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_stop_discovery (struct hci_request*) ; 

__attribute__((used)) static int stop_discovery(struct hci_request *req, unsigned long opt)
{
	hci_dev_lock(req->hdev);
	hci_req_stop_discovery(req);
	hci_dev_unlock(req->hdev);

	return 0;
}
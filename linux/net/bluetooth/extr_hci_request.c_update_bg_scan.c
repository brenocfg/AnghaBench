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
 int /*<<< orphan*/  __hci_update_background_scan (struct hci_request*) ; 
 int /*<<< orphan*/  hci_dev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_bg_scan(struct hci_request *req, unsigned long opt)
{
	hci_dev_lock(req->hdev);
	__hci_update_background_scan(req);
	hci_dev_unlock(req->hdev);
	return 0;
}
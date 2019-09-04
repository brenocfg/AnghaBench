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
struct hci_request {TYPE_1__* hdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISCOV_BREDR_INQUIRY_LEN ; 
 int active_scan (struct hci_request*,unsigned long) ; 
 int bredr_inquiry (struct hci_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int interleaved_discov(struct hci_request *req, unsigned long opt)
{
	int err;

	BT_DBG("%s", req->hdev->name);

	err = active_scan(req, opt);
	if (err)
		return err;

	return bredr_inquiry(req, DISCOV_BREDR_INQUIRY_LEN);
}
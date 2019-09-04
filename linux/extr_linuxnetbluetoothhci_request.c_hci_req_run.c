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
typedef  int /*<<< orphan*/  hci_req_complete_t ;

/* Variables and functions */
 int req_run (struct hci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_req_run(struct hci_request *req, hci_req_complete_t complete)
{
	return req_run(req, complete, NULL);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct q_res_req_compl {int /*<<< orphan*/  host_event; TYPE_3__* hpdev; } ;
struct pci_response {int /*<<< orphan*/  status; } ;
struct pci_q_res_req_response {int /*<<< orphan*/ * probed_bar; } ;
struct TYPE_6__ {int /*<<< orphan*/ * probed_bar; TYPE_2__* hbus; } ;
struct TYPE_5__ {TYPE_1__* hdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void q_resource_requirements(void *context, struct pci_response *resp,
				    int resp_packet_size)
{
	struct q_res_req_compl *completion = context;
	struct pci_q_res_req_response *q_res_req =
		(struct pci_q_res_req_response *)resp;
	int i;

	if (resp->status < 0) {
		dev_err(&completion->hpdev->hbus->hdev->device,
			"query resource requirements failed: %x\n",
			resp->status);
	} else {
		for (i = 0; i < 6; i++) {
			completion->hpdev->probed_bar[i] =
				q_res_req->probed_bar[i];
		}
	}

	complete(&completion->host_event);
}
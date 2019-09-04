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
struct pci_response {int /*<<< orphan*/  status; } ;
struct pci_create_int_response {int /*<<< orphan*/  int_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_event; int /*<<< orphan*/  completion_status; } ;
struct compose_comp_ctxt {TYPE_1__ comp_pkt; int /*<<< orphan*/  int_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hv_pci_compose_compl(void *context, struct pci_response *resp,
				 int resp_packet_size)
{
	struct compose_comp_ctxt *comp_pkt = context;
	struct pci_create_int_response *int_resp =
		(struct pci_create_int_response *)resp;

	comp_pkt->comp_pkt.completion_status = resp->status;
	comp_pkt->int_desc = int_resp->int_desc;
	complete(&comp_pkt->comp_pkt.host_event);
}
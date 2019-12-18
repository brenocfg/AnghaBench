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
struct garp_applicant {int /*<<< orphan*/ * pdu; int /*<<< orphan*/  queue; TYPE_2__* app; TYPE_3__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  group_address; } ;
struct TYPE_5__ {TYPE_1__ proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_PDU_CMD ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_U ; 
 int /*<<< orphan*/  LLC_SAP_BSPAN ; 
 int /*<<< orphan*/  garp_pdu_append_end_mark (struct garp_applicant*) ; 
 int /*<<< orphan*/  llc_mac_hdr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_header_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_ui_cmd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void garp_pdu_queue(struct garp_applicant *app)
{
	if (!app->pdu)
		return;

	garp_pdu_append_end_mark(app);
	garp_pdu_append_end_mark(app);

	llc_pdu_header_init(app->pdu, LLC_PDU_TYPE_U, LLC_SAP_BSPAN,
			    LLC_SAP_BSPAN, LLC_PDU_CMD);
	llc_pdu_init_as_ui_cmd(app->pdu);
	llc_mac_hdr_init(app->pdu, app->dev->dev_addr,
			 app->app->proto.group_address);

	skb_queue_tail(&app->queue, app->pdu);
	app->pdu = NULL;
}
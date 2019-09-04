#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mrp_applicant {TYPE_3__* pdu; int /*<<< orphan*/  queue; TYPE_7__* dev; TYPE_2__* app; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_11__ {scalar_t__ mh; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int /*<<< orphan*/  group_address; TYPE_1__ pkttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hard_header (TYPE_3__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* mrp_cb (TYPE_3__*) ; 
 int /*<<< orphan*/  mrp_pdu_append_end_mark (struct mrp_applicant*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void mrp_pdu_queue(struct mrp_applicant *app)
{
	if (!app->pdu)
		return;

	if (mrp_cb(app->pdu)->mh)
		mrp_pdu_append_end_mark(app);
	mrp_pdu_append_end_mark(app);

	dev_hard_header(app->pdu, app->dev, ntohs(app->app->pkttype.type),
			app->app->group_address, app->dev->dev_addr,
			app->pdu->len);

	skb_queue_tail(&app->queue, app->pdu);
	app->pdu = NULL;
}
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
struct garp_attr_hdr {unsigned int len; int event; int /*<<< orphan*/  data; } ;
struct garp_attr {int dlen; int /*<<< orphan*/  data; scalar_t__ type; } ;
struct garp_applicant {int /*<<< orphan*/  pdu; } ;
typedef  enum garp_attr_event { ____Placeholder_garp_attr_event } garp_attr_event ;
struct TYPE_2__ {scalar_t__ cur_type; } ;

/* Variables and functions */
 struct garp_attr_hdr* __skb_put (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* garp_cb (int /*<<< orphan*/ ) ; 
 scalar_t__ garp_pdu_append_end_mark (struct garp_applicant*) ; 
 scalar_t__ garp_pdu_append_msg (struct garp_applicant*,scalar_t__) ; 
 int garp_pdu_init (struct garp_applicant*) ; 
 int /*<<< orphan*/  garp_pdu_queue (struct garp_applicant*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int skb_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int garp_pdu_append_attr(struct garp_applicant *app,
				const struct garp_attr *attr,
				enum garp_attr_event event)
{
	struct garp_attr_hdr *ga;
	unsigned int len;
	int err;
again:
	if (!app->pdu) {
		err = garp_pdu_init(app);
		if (err < 0)
			return err;
	}

	if (garp_cb(app->pdu)->cur_type != attr->type) {
		if (garp_cb(app->pdu)->cur_type &&
		    garp_pdu_append_end_mark(app) < 0)
			goto queue;
		if (garp_pdu_append_msg(app, attr->type) < 0)
			goto queue;
	}

	len = sizeof(*ga) + attr->dlen;
	if (skb_tailroom(app->pdu) < len)
		goto queue;
	ga = __skb_put(app->pdu, len);
	ga->len   = len;
	ga->event = event;
	memcpy(ga->data, attr->data, attr->dlen);
	return 0;

queue:
	garp_pdu_queue(app);
	goto again;
}
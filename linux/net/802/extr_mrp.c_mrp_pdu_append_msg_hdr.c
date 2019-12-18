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
typedef  void* u8 ;
struct mrp_msg_hdr {void* attrlen; void* attrtype; } ;
struct mrp_applicant {int /*<<< orphan*/  pdu; } ;
struct TYPE_2__ {struct mrp_msg_hdr* mh; int /*<<< orphan*/ * vah; } ;

/* Variables and functions */
 struct mrp_msg_hdr* __skb_put (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mrp_cb (int /*<<< orphan*/ ) ; 
 scalar_t__ mrp_pdu_append_end_mark (struct mrp_applicant*) ; 
 int skb_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrp_pdu_append_msg_hdr(struct mrp_applicant *app,
				  u8 attrtype, u8 attrlen)
{
	struct mrp_msg_hdr *mh;

	if (mrp_cb(app->pdu)->mh) {
		if (mrp_pdu_append_end_mark(app) < 0)
			return -1;
		mrp_cb(app->pdu)->mh = NULL;
		mrp_cb(app->pdu)->vah = NULL;
	}

	if (skb_tailroom(app->pdu) < sizeof(*mh))
		return -1;
	mh = __skb_put(app->pdu, sizeof(*mh));
	mh->attrtype = attrtype;
	mh->attrlen = attrlen;
	mrp_cb(app->pdu)->mh = mh;
	return 0;
}
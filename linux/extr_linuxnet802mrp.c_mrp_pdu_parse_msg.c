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
struct sk_buff {int len; } ;
struct mrp_msg_hdr {int dummy; } ;
struct mrp_applicant {TYPE_1__* app; } ;
typedef  int /*<<< orphan*/  _mh ;
struct TYPE_6__ {TYPE_2__* mh; } ;
struct TYPE_5__ {scalar_t__ attrtype; scalar_t__ attrlen; } ;
struct TYPE_4__ {scalar_t__ maxattr; } ;

/* Variables and functions */
 TYPE_3__* mrp_cb (struct sk_buff*) ; 
 scalar_t__ mrp_pdu_parse_end_mark (struct sk_buff*,int*) ; 
 scalar_t__ mrp_pdu_parse_vecattr (struct mrp_applicant*,struct sk_buff*,int*) ; 
 TYPE_2__* skb_header_pointer (struct sk_buff*,int,int,struct mrp_msg_hdr*) ; 

__attribute__((used)) static int mrp_pdu_parse_msg(struct mrp_applicant *app, struct sk_buff *skb,
			     int *offset)
{
	struct mrp_msg_hdr _mh;

	mrp_cb(skb)->mh = skb_header_pointer(skb, *offset, sizeof(_mh), &_mh);
	if (!mrp_cb(skb)->mh)
		return -1;
	*offset += sizeof(_mh);

	if (mrp_cb(skb)->mh->attrtype == 0 ||
	    mrp_cb(skb)->mh->attrtype > app->app->maxattr ||
	    mrp_cb(skb)->mh->attrlen == 0)
		return -1;

	while (skb->len > *offset) {
		if (mrp_pdu_parse_end_mark(skb, offset) < 0)
			break;
		if (mrp_pdu_parse_vecattr(app, skb, offset) < 0)
			return -1;
	}
	return 0;
}
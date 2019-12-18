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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct garp_attr_hdr {int len; int event; int /*<<< orphan*/  data; } ;
struct garp_attr {int dummy; } ;
struct garp_applicant {TYPE_1__* app; } ;
typedef  enum garp_event { ____Placeholder_garp_event } garp_event ;
struct TYPE_2__ {int /*<<< orphan*/  maxattr; } ;

/* Variables and functions */
#define  GARP_EMPTY 132 
 int GARP_EVENT_R_EMPTY ; 
 int GARP_EVENT_R_JOIN_EMPTY ; 
 int GARP_EVENT_R_JOIN_IN ; 
 int GARP_EVENT_R_LEAVE_EMPTY ; 
#define  GARP_JOIN_EMPTY 131 
#define  GARP_JOIN_IN 130 
#define  GARP_LEAVE_ALL 129 
#define  GARP_LEAVE_EMPTY 128 
 int /*<<< orphan*/  garp_attr_event (struct garp_applicant*,struct garp_attr*,int) ; 
 struct garp_attr* garp_attr_lookup (struct garp_applicant*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  garp_gid_event (struct garp_applicant*,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int garp_pdu_parse_attr(struct garp_applicant *app, struct sk_buff *skb,
			       u8 attrtype)
{
	const struct garp_attr_hdr *ga;
	struct garp_attr *attr;
	enum garp_event event;
	unsigned int dlen;

	if (!pskb_may_pull(skb, sizeof(*ga)))
		return -1;
	ga = (struct garp_attr_hdr *)skb->data;
	if (ga->len < sizeof(*ga))
		return -1;

	if (!pskb_may_pull(skb, ga->len))
		return -1;
	skb_pull(skb, ga->len);
	dlen = sizeof(*ga) - ga->len;

	if (attrtype > app->app->maxattr)
		return 0;

	switch (ga->event) {
	case GARP_LEAVE_ALL:
		if (dlen != 0)
			return -1;
		garp_gid_event(app, GARP_EVENT_R_LEAVE_EMPTY);
		return 0;
	case GARP_JOIN_EMPTY:
		event = GARP_EVENT_R_JOIN_EMPTY;
		break;
	case GARP_JOIN_IN:
		event = GARP_EVENT_R_JOIN_IN;
		break;
	case GARP_LEAVE_EMPTY:
		event = GARP_EVENT_R_LEAVE_EMPTY;
		break;
	case GARP_EMPTY:
		event = GARP_EVENT_R_EMPTY;
		break;
	default:
		return 0;
	}

	if (dlen == 0)
		return -1;
	attr = garp_attr_lookup(app, ga->data, dlen, attrtype);
	if (attr == NULL)
		return 0;
	garp_attr_event(app, attr, event);
	return 0;
}
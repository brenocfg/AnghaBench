#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mrp_attr {int dummy; } ;
struct mrp_applicant {int dummy; } ;
typedef  enum mrp_vecattr_event { ____Placeholder_mrp_vecattr_event } mrp_vecattr_event ;
typedef  enum mrp_event { ____Placeholder_mrp_event } mrp_event ;
struct TYPE_4__ {TYPE_1__* mh; int /*<<< orphan*/  attrvalue; } ;
struct TYPE_3__ {int /*<<< orphan*/  attrtype; int /*<<< orphan*/  attrlen; } ;

/* Variables and functions */
 int MRP_EVENT_R_IN ; 
 int MRP_EVENT_R_JOIN_IN ; 
 int MRP_EVENT_R_JOIN_MT ; 
 int MRP_EVENT_R_LV ; 
 int MRP_EVENT_R_MT ; 
 int MRP_EVENT_R_NEW ; 
#define  MRP_VECATTR_EVENT_IN 133 
#define  MRP_VECATTR_EVENT_JOIN_IN 132 
#define  MRP_VECATTR_EVENT_JOIN_MT 131 
#define  MRP_VECATTR_EVENT_LV 130 
#define  MRP_VECATTR_EVENT_MT 129 
#define  MRP_VECATTR_EVENT_NEW 128 
 int /*<<< orphan*/  mrp_attr_event (struct mrp_applicant*,struct mrp_attr*,int) ; 
 struct mrp_attr* mrp_attr_lookup (struct mrp_applicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mrp_cb (struct sk_buff*) ; 

__attribute__((used)) static void mrp_pdu_parse_vecattr_event(struct mrp_applicant *app,
					struct sk_buff *skb,
					enum mrp_vecattr_event vaevent)
{
	struct mrp_attr *attr;
	enum mrp_event event;

	attr = mrp_attr_lookup(app, mrp_cb(skb)->attrvalue,
			       mrp_cb(skb)->mh->attrlen,
			       mrp_cb(skb)->mh->attrtype);
	if (attr == NULL)
		return;

	switch (vaevent) {
	case MRP_VECATTR_EVENT_NEW:
		event = MRP_EVENT_R_NEW;
		break;
	case MRP_VECATTR_EVENT_JOIN_IN:
		event = MRP_EVENT_R_JOIN_IN;
		break;
	case MRP_VECATTR_EVENT_IN:
		event = MRP_EVENT_R_IN;
		break;
	case MRP_VECATTR_EVENT_JOIN_MT:
		event = MRP_EVENT_R_JOIN_MT;
		break;
	case MRP_VECATTR_EVENT_MT:
		event = MRP_EVENT_R_MT;
		break;
	case MRP_VECATTR_EVENT_LV:
		event = MRP_EVENT_R_LV;
		break;
	default:
		return;
	}

	mrp_attr_event(app, attr, event);
}
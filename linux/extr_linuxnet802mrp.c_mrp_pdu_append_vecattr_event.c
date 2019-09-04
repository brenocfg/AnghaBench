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
typedef  int u8 ;
typedef  int u16 ;
struct mrp_attr {scalar_t__ type; scalar_t__ len; int /*<<< orphan*/  value; } ;
struct mrp_applicant {int /*<<< orphan*/  pdu; } ;
typedef  enum mrp_vecattr_event { ____Placeholder_mrp_vecattr_event } mrp_vecattr_event ;
struct TYPE_6__ {int /*<<< orphan*/  attrvalue; TYPE_2__* vah; TYPE_1__* mh; } ;
struct TYPE_5__ {int /*<<< orphan*/  lenflags; } ;
struct TYPE_4__ {scalar_t__ attrtype; scalar_t__ attrlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __MRP_VECATTR_EVENT_MAX ; 
 int* __skb_put (int /*<<< orphan*/ ,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrp_attrvalue_inc (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* mrp_cb (int /*<<< orphan*/ ) ; 
 scalar_t__ mrp_pdu_append_msg_hdr (struct mrp_applicant*,scalar_t__,scalar_t__) ; 
 scalar_t__ mrp_pdu_append_vecattr_hdr (struct mrp_applicant*,int /*<<< orphan*/ ,scalar_t__) ; 
 int mrp_pdu_init (struct mrp_applicant*) ; 
 int /*<<< orphan*/  mrp_pdu_queue (struct mrp_applicant*) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int skb_tail_pointer (int /*<<< orphan*/ ) ; 
 int skb_tailroom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrp_pdu_append_vecattr_event(struct mrp_applicant *app,
					const struct mrp_attr *attr,
					enum mrp_vecattr_event vaevent)
{
	u16 len, pos;
	u8 *vaevents;
	int err;
again:
	if (!app->pdu) {
		err = mrp_pdu_init(app);
		if (err < 0)
			return err;
	}

	/* If there is no Message header in the PDU, or the Message header is
	 * for a different attribute type, add an EndMark (if necessary) and a
	 * new Message header to the PDU.
	 */
	if (!mrp_cb(app->pdu)->mh ||
	    mrp_cb(app->pdu)->mh->attrtype != attr->type ||
	    mrp_cb(app->pdu)->mh->attrlen != attr->len) {
		if (mrp_pdu_append_msg_hdr(app, attr->type, attr->len) < 0)
			goto queue;
	}

	/* If there is no VectorAttribute header for this Message in the PDU,
	 * or this attribute's value does not sequentially follow the previous
	 * attribute's value, add a new VectorAttribute header to the PDU.
	 */
	if (!mrp_cb(app->pdu)->vah ||
	    memcmp(mrp_cb(app->pdu)->attrvalue, attr->value, attr->len)) {
		if (mrp_pdu_append_vecattr_hdr(app, attr->value, attr->len) < 0)
			goto queue;
	}

	len = be16_to_cpu(get_unaligned(&mrp_cb(app->pdu)->vah->lenflags));
	pos = len % 3;

	/* Events are packed into Vectors in the PDU, three to a byte. Add a
	 * byte to the end of the Vector if necessary.
	 */
	if (!pos) {
		if (skb_tailroom(app->pdu) < sizeof(u8))
			goto queue;
		vaevents = __skb_put(app->pdu, sizeof(u8));
	} else {
		vaevents = (u8 *)(skb_tail_pointer(app->pdu) - sizeof(u8));
	}

	switch (pos) {
	case 0:
		*vaevents = vaevent * (__MRP_VECATTR_EVENT_MAX *
				       __MRP_VECATTR_EVENT_MAX);
		break;
	case 1:
		*vaevents += vaevent * __MRP_VECATTR_EVENT_MAX;
		break;
	case 2:
		*vaevents += vaevent;
		break;
	default:
		WARN_ON(1);
	}

	/* Increment the length of the VectorAttribute in the PDU, as well as
	 * the value of the next attribute that would continue its Vector.
	 */
	put_unaligned(cpu_to_be16(++len), &mrp_cb(app->pdu)->vah->lenflags);
	mrp_attrvalue_inc(mrp_cb(app->pdu)->attrvalue, attr->len);

	return 0;

queue:
	mrp_pdu_queue(app);
	goto again;
}
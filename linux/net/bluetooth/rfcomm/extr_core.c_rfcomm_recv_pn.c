#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ data; } ;
struct rfcomm_session {int /*<<< orphan*/  initiator; int /*<<< orphan*/  state; } ;
struct rfcomm_pn {scalar_t__ dlci; } ;
struct rfcomm_dlc {int state; int /*<<< orphan*/  addr; scalar_t__ dlci; } ;

/* Variables and functions */
#define  BT_CONFIG 128 
 int BT_CONNECT ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int /*<<< orphan*/ ,scalar_t__) ; 
 int BT_OPEN ; 
 int /*<<< orphan*/  __addr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ __srv_channel (scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_apply_pn (struct rfcomm_dlc*,int,struct rfcomm_pn*) ; 
 scalar_t__ rfcomm_connect_ind (struct rfcomm_session*,scalar_t__,struct rfcomm_dlc**) ; 
 struct rfcomm_dlc* rfcomm_dlc_get (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_dlc_link (struct rfcomm_session*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_send_dm (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_send_pn (struct rfcomm_session*,int /*<<< orphan*/ ,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_send_sabm (struct rfcomm_session*,scalar_t__) ; 

__attribute__((used)) static int rfcomm_recv_pn(struct rfcomm_session *s, int cr, struct sk_buff *skb)
{
	struct rfcomm_pn *pn = (void *) skb->data;
	struct rfcomm_dlc *d;
	u8 dlci = pn->dlci;

	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	if (!dlci)
		return 0;

	d = rfcomm_dlc_get(s, dlci);
	if (d) {
		if (cr) {
			/* PN request */
			rfcomm_apply_pn(d, cr, pn);
			rfcomm_send_pn(s, 0, d);
		} else {
			/* PN response */
			switch (d->state) {
			case BT_CONFIG:
				rfcomm_apply_pn(d, cr, pn);

				d->state = BT_CONNECT;
				rfcomm_send_sabm(s, d->dlci);
				break;
			}
		}
	} else {
		u8 channel = __srv_channel(dlci);

		if (!cr)
			return 0;

		/* PN request for non existing DLC.
		 * Assume incoming connection. */
		if (rfcomm_connect_ind(s, channel, &d)) {
			d->dlci = dlci;
			d->addr = __addr(s->initiator, dlci);
			rfcomm_dlc_link(s, d);

			rfcomm_apply_pn(d, cr, pn);

			d->state = BT_OPEN;
			rfcomm_send_pn(s, 0, d);
		} else {
			rfcomm_send_dm(s, dlci);
		}
	}
	return 0;
}
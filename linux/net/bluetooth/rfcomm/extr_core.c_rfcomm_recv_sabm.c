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
struct rfcomm_session {scalar_t__ state; int /*<<< orphan*/  initiator; } ;
struct rfcomm_dlc {scalar_t__ state; int /*<<< orphan*/  addr; scalar_t__ dlci; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,scalar_t__,scalar_t__) ; 
 scalar_t__ BT_OPEN ; 
 int /*<<< orphan*/  __addr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ __srv_channel (scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_check_accept (struct rfcomm_dlc*) ; 
 scalar_t__ rfcomm_connect_ind (struct rfcomm_session*,scalar_t__,struct rfcomm_dlc**) ; 
 struct rfcomm_dlc* rfcomm_dlc_get (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_dlc_link (struct rfcomm_session*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_process_connect (struct rfcomm_session*) ; 
 int /*<<< orphan*/  rfcomm_send_dm (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_send_ua (struct rfcomm_session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfcomm_recv_sabm(struct rfcomm_session *s, u8 dlci)
{
	struct rfcomm_dlc *d;
	u8 channel;

	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	if (!dlci) {
		rfcomm_send_ua(s, 0);

		if (s->state == BT_OPEN) {
			s->state = BT_CONNECTED;
			rfcomm_process_connect(s);
		}
		return 0;
	}

	/* Check if DLC exists */
	d = rfcomm_dlc_get(s, dlci);
	if (d) {
		if (d->state == BT_OPEN) {
			/* DLC was previously opened by PN request */
			rfcomm_check_accept(d);
		}
		return 0;
	}

	/* Notify socket layer about incoming connection */
	channel = __srv_channel(dlci);
	if (rfcomm_connect_ind(s, channel, &d)) {
		d->dlci = dlci;
		d->addr = __addr(s->initiator, dlci);
		rfcomm_dlc_link(s, d);

		rfcomm_check_accept(d);
	} else {
		rfcomm_send_dm(s, dlci);
	}

	return 0;
}
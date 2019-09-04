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
struct rfcomm_session {int state; int /*<<< orphan*/  dlcs; } ;
struct rfcomm_dlc {int state; int /*<<< orphan*/  v24_sig; int /*<<< orphan*/  (* state_change ) (struct rfcomm_dlc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BT_CLOSED ; 
#define  BT_CONNECT 129 
 void* BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int,scalar_t__) ; 
#define  BT_DISCONN 128 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  __rfcomm_dlc_close (struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dlc_clear_timer (struct rfcomm_dlc*) ; 
 struct rfcomm_dlc* rfcomm_dlc_get (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_process_connect (struct rfcomm_session*) ; 
 int /*<<< orphan*/  rfcomm_send_disc (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_send_dm (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_send_msc (struct rfcomm_session*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_session_clear_timer (struct rfcomm_session*) ; 
 struct rfcomm_session* rfcomm_session_close (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rfcomm_session *rfcomm_recv_ua(struct rfcomm_session *s, u8 dlci)
{
	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	if (dlci) {
		/* Data channel */
		struct rfcomm_dlc *d = rfcomm_dlc_get(s, dlci);
		if (!d) {
			rfcomm_send_dm(s, dlci);
			return s;
		}

		switch (d->state) {
		case BT_CONNECT:
			rfcomm_dlc_clear_timer(d);

			rfcomm_dlc_lock(d);
			d->state = BT_CONNECTED;
			d->state_change(d, 0);
			rfcomm_dlc_unlock(d);

			rfcomm_send_msc(s, 1, dlci, d->v24_sig);
			break;

		case BT_DISCONN:
			d->state = BT_CLOSED;
			__rfcomm_dlc_close(d, 0);

			if (list_empty(&s->dlcs)) {
				s->state = BT_DISCONN;
				rfcomm_send_disc(s, 0);
				rfcomm_session_clear_timer(s);
			}

			break;
		}
	} else {
		/* Control channel */
		switch (s->state) {
		case BT_CONNECT:
			s->state = BT_CONNECTED;
			rfcomm_process_connect(s);
			break;

		case BT_DISCONN:
			s = rfcomm_session_close(s, ECONNRESET);
			break;
		}
	}
	return s;
}
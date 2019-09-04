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
struct rfcomm_session {scalar_t__ state; } ;
struct rfcomm_dlc {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ BT_CLOSED ; 
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECT ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,scalar_t__,scalar_t__) ; 
 int ECONNREFUSED ; 
 int ECONNRESET ; 
 int /*<<< orphan*/  __rfcomm_dlc_close (struct rfcomm_dlc*,int) ; 
 struct rfcomm_dlc* rfcomm_dlc_get (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_send_dm (struct rfcomm_session*,scalar_t__) ; 
 int /*<<< orphan*/  rfcomm_send_ua (struct rfcomm_session*,scalar_t__) ; 
 struct rfcomm_session* rfcomm_session_close (struct rfcomm_session*,int) ; 

__attribute__((used)) static struct rfcomm_session *rfcomm_recv_disc(struct rfcomm_session *s,
					       u8 dlci)
{
	int err = 0;

	BT_DBG("session %p state %ld dlci %d", s, s->state, dlci);

	if (dlci) {
		struct rfcomm_dlc *d = rfcomm_dlc_get(s, dlci);
		if (d) {
			rfcomm_send_ua(s, dlci);

			if (d->state == BT_CONNECT || d->state == BT_CONFIG)
				err = ECONNREFUSED;
			else
				err = ECONNRESET;

			d->state = BT_CLOSED;
			__rfcomm_dlc_close(d, err);
		} else
			rfcomm_send_dm(s, dlci);

	} else {
		rfcomm_send_ua(s, 0);

		if (s->state == BT_CONNECT)
			err = ECONNREFUSED;
		else
			err = ECONNRESET;

		s = rfcomm_session_close(s, err);
	}
	return s;
}
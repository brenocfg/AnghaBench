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
struct rfcomm_session {int dummy; } ;
struct rfcomm_dlc {int /*<<< orphan*/  dlci; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  state; struct rfcomm_session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DISCONN ; 
 int RFCOMM_DISC_TIMEOUT ; 
 int /*<<< orphan*/  rfcomm_dlc_set_timer (struct rfcomm_dlc*,int) ; 
 int /*<<< orphan*/  rfcomm_queue_disc (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_send_disc (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rfcomm_dlc_disconn(struct rfcomm_dlc *d)
{
	struct rfcomm_session *s = d->session;

	d->state = BT_DISCONN;
	if (skb_queue_empty(&d->tx_queue)) {
		rfcomm_send_disc(s, d->dlci);
		rfcomm_dlc_set_timer(d, RFCOMM_DISC_TIMEOUT);
	} else {
		rfcomm_queue_disc(d);
		rfcomm_dlc_set_timer(d, RFCOMM_DISC_TIMEOUT * 2);
	}
}
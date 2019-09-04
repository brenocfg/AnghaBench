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
struct rfcomm_dlc {int /*<<< orphan*/  flags; int /*<<< orphan*/  (* state_change ) (struct rfcomm_dlc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  state; scalar_t__ defer_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONNECT2 ; 
 int /*<<< orphan*/  RFCOMM_AUTH_PENDING ; 
 int /*<<< orphan*/  RFCOMM_AUTH_TIMEOUT ; 
 int /*<<< orphan*/  RFCOMM_DEFER_SETUP ; 
 scalar_t__ rfcomm_check_security (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_accept (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_set_timer (struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfcomm_check_accept(struct rfcomm_dlc *d)
{
	if (rfcomm_check_security(d)) {
		if (d->defer_setup) {
			set_bit(RFCOMM_DEFER_SETUP, &d->flags);
			rfcomm_dlc_set_timer(d, RFCOMM_AUTH_TIMEOUT);

			rfcomm_dlc_lock(d);
			d->state = BT_CONNECT2;
			d->state_change(d, 0);
			rfcomm_dlc_unlock(d);
		} else
			rfcomm_dlc_accept(d);
	} else {
		set_bit(RFCOMM_AUTH_PENDING, &d->flags);
		rfcomm_dlc_set_timer(d, RFCOMM_AUTH_TIMEOUT);
	}
}
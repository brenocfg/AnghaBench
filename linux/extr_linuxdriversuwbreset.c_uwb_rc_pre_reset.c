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
struct uwb_rc {int /*<<< orphan*/  (* stop ) (struct uwb_rc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_radio_reset_state (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rsv_remove_all (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwbd_flush (struct uwb_rc*) ; 

void uwb_rc_pre_reset(struct uwb_rc *rc)
{
	rc->stop(rc);
	uwbd_flush(rc);

	uwb_radio_reset_state(rc);
	uwb_rsv_remove_all(rc);
}
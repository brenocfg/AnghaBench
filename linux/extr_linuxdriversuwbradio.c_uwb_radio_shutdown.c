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
struct uwb_rc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_radio_reset_state (struct uwb_rc*) ; 
 int /*<<< orphan*/  uwb_rc_reset (struct uwb_rc*) ; 

void uwb_radio_shutdown(struct uwb_rc *rc)
{
	uwb_radio_reset_state(rc);
	uwb_rc_reset(rc);
}
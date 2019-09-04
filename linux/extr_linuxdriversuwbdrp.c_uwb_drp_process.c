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
struct uwb_rc_evt_drp {int dummy; } ;
struct uwb_rc {int dummy; } ;
struct uwb_ie_drp {int dummy; } ;
struct uwb_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ UWB_DRP_TYPE_ALIEN_BP ; 
 int /*<<< orphan*/  uwb_drp_handle_alien_drp (struct uwb_rc*,struct uwb_ie_drp*) ; 
 scalar_t__ uwb_drp_involves_us (struct uwb_rc*,struct uwb_ie_drp*) ; 
 int /*<<< orphan*/  uwb_drp_process_involved (struct uwb_rc*,struct uwb_dev*,struct uwb_rc_evt_drp*,struct uwb_ie_drp*) ; 
 int /*<<< orphan*/  uwb_drp_process_not_involved (struct uwb_rc*,struct uwb_rc_evt_drp*,struct uwb_ie_drp*) ; 
 scalar_t__ uwb_ie_drp_type (struct uwb_ie_drp*) ; 

__attribute__((used)) static void uwb_drp_process(struct uwb_rc *rc, struct uwb_rc_evt_drp *drp_evt,
			    struct uwb_dev *src, struct uwb_ie_drp *drp_ie)
{
	if (uwb_ie_drp_type(drp_ie) == UWB_DRP_TYPE_ALIEN_BP)
		uwb_drp_handle_alien_drp(rc, drp_ie);
	else if (uwb_drp_involves_us(rc, drp_ie))
		uwb_drp_process_involved(rc, src, drp_evt, drp_ie);
	else
		uwb_drp_process_not_involved(rc, drp_evt, drp_ie);
}
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
struct regulatory_request {scalar_t__ initiator; int /*<<< orphan*/  alpha2; } ;
typedef  enum reg_request_treatment { ____Placeholder_reg_request_treatment } reg_request_treatment ;

/* Variables and functions */
 scalar_t__ NL80211_REGDOM_SET_BY_CORE ; 
 scalar_t__ NL80211_REGDOM_SET_BY_DRIVER ; 
 int REG_REQ_ALREADY_SET ; 
 int REG_REQ_INTERSECT ; 
 int REG_REQ_OK ; 
 struct regulatory_request* get_last_request () ; 
 scalar_t__ regdom_changes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum reg_request_treatment
__reg_process_hint_driver(struct regulatory_request *driver_request)
{
	struct regulatory_request *lr = get_last_request();

	if (lr->initiator == NL80211_REGDOM_SET_BY_CORE) {
		if (regdom_changes(driver_request->alpha2))
			return REG_REQ_OK;
		return REG_REQ_ALREADY_SET;
	}

	/*
	 * This would happen if you unplug and plug your card
	 * back in or if you add a new device for which the previously
	 * loaded card also agrees on the regulatory domain.
	 */
	if (lr->initiator == NL80211_REGDOM_SET_BY_DRIVER &&
	    !regdom_changes(driver_request->alpha2))
		return REG_REQ_ALREADY_SET;

	return REG_REQ_INTERSECT;
}
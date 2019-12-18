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
struct regulatory_request {scalar_t__ initiator; int /*<<< orphan*/  alpha2; scalar_t__ intersect; } ;
typedef  enum reg_request_treatment { ____Placeholder_reg_request_treatment } reg_request_treatment ;

/* Variables and functions */
 scalar_t__ NL80211_REGDOM_SET_BY_CORE ; 
 scalar_t__ NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 scalar_t__ NL80211_REGDOM_SET_BY_DRIVER ; 
 scalar_t__ NL80211_REGDOM_SET_BY_USER ; 
 int REG_REQ_ALREADY_SET ; 
 int REG_REQ_IGNORE ; 
 int REG_REQ_INTERSECT ; 
 int REG_REQ_OK ; 
 struct regulatory_request* get_last_request () ; 
 int reg_ignore_cell_hint (struct regulatory_request*) ; 
 scalar_t__ reg_request_cell_base (struct regulatory_request*) ; 
 scalar_t__ regdom_changes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum reg_request_treatment
__reg_process_hint_user(struct regulatory_request *user_request)
{
	struct regulatory_request *lr = get_last_request();

	if (reg_request_cell_base(user_request))
		return reg_ignore_cell_hint(user_request);

	if (reg_request_cell_base(lr))
		return REG_REQ_IGNORE;

	if (lr->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE)
		return REG_REQ_INTERSECT;
	/*
	 * If the user knows better the user should set the regdom
	 * to their country before the IE is picked up
	 */
	if (lr->initiator == NL80211_REGDOM_SET_BY_USER &&
	    lr->intersect)
		return REG_REQ_IGNORE;
	/*
	 * Process user requests only after previous user/driver/core
	 * requests have been processed
	 */
	if ((lr->initiator == NL80211_REGDOM_SET_BY_CORE ||
	     lr->initiator == NL80211_REGDOM_SET_BY_DRIVER ||
	     lr->initiator == NL80211_REGDOM_SET_BY_USER) &&
	    regdom_changes(lr->alpha2))
		return REG_REQ_IGNORE;

	if (!regdom_changes(user_request->alpha2))
		return REG_REQ_ALREADY_SET;

	return REG_REQ_OK;
}
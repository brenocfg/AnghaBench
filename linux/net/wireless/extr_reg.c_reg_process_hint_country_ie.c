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
struct wiphy {int dummy; } ;
struct regulatory_request {int intersect; int processed; } ;
typedef  enum reg_request_treatment { ____Placeholder_reg_request_treatment } reg_request_treatment ;

/* Variables and functions */
#define  REG_REQ_ALREADY_SET 131 
#define  REG_REQ_IGNORE 130 
#define  REG_REQ_INTERSECT 129 
#define  REG_REQ_OK 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int __reg_process_hint_country_ie (struct wiphy*,struct regulatory_request*) ; 
 int /*<<< orphan*/  reg_free_request (struct regulatory_request*) ; 
 scalar_t__ reg_query_database (struct regulatory_request*) ; 
 int /*<<< orphan*/  reg_update_last_request (struct regulatory_request*) ; 

__attribute__((used)) static enum reg_request_treatment
reg_process_hint_country_ie(struct wiphy *wiphy,
			    struct regulatory_request *country_ie_request)
{
	enum reg_request_treatment treatment;

	treatment = __reg_process_hint_country_ie(wiphy, country_ie_request);

	switch (treatment) {
	case REG_REQ_OK:
		break;
	case REG_REQ_IGNORE:
		return REG_REQ_IGNORE;
	case REG_REQ_ALREADY_SET:
		reg_free_request(country_ie_request);
		return REG_REQ_ALREADY_SET;
	case REG_REQ_INTERSECT:
		/*
		 * This doesn't happen yet, not sure we
		 * ever want to support it for this case.
		 */
		WARN_ONCE(1, "Unexpected intersection for country elements");
		return REG_REQ_IGNORE;
	}

	country_ie_request->intersect = false;
	country_ie_request->processed = false;

	if (reg_query_database(country_ie_request)) {
		reg_update_last_request(country_ie_request);
		return REG_REQ_OK;
	}

	return REG_REQ_IGNORE;
}
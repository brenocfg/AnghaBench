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
struct regulatory_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_CMD_REG_CHANGE ; 
 int /*<<< orphan*/  nl80211_common_reg_change_event (int /*<<< orphan*/ ,struct regulatory_request*) ; 

__attribute__((used)) static inline void
nl80211_send_reg_change_event(struct regulatory_request *request)
{
	nl80211_common_reg_change_event(NL80211_CMD_REG_CHANGE, request);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_he_operation {int dummy; } ;
struct TYPE_2__ {struct ieee80211_he_operation he_operation; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ieee80211_he_operation*,int /*<<< orphan*/ ,int) ; 

void
ieee80211_he_op_ie_to_bss_conf(struct ieee80211_vif *vif,
			const struct ieee80211_he_operation *he_op_ie_elem)
{
	struct ieee80211_he_operation *he_operation =
					&vif->bss_conf.he_operation;

	if (!he_op_ie_elem) {
		memset(he_operation, 0, sizeof(*he_operation));
		return;
	}

	vif->bss_conf.he_operation = *he_op_ie_elem;
}
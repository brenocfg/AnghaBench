#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_sub_if_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dialog_token; int /*<<< orphan*/  msr_elem; } ;
struct TYPE_6__ {TYPE_1__ measurement; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_send_refuse_measurement_request (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee80211_process_measurement_req(struct ieee80211_sub_if_data *sdata,
				       struct ieee80211_mgmt *mgmt,
				       size_t len)
{
	/*
	 * Ignoring measurement request is spec violation.
	 * Mandatory measurements must be reported optional
	 * measurements might be refused or reported incapable
	 * For now just refuse
	 * TODO: Answer basic measurement as unmeasured
	 */
	ieee80211_send_refuse_measurement_request(sdata,
			&mgmt->u.action.u.measurement.msr_elem,
			mgmt->sa, mgmt->bssid,
			mgmt->u.action.u.measurement.dialog_token);
}
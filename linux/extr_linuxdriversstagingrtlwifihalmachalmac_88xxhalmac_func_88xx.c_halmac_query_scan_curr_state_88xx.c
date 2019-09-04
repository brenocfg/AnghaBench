#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int scan_cmd_construct_state; } ;
struct TYPE_4__ {TYPE_1__ scan_state_set; } ;
struct halmac_adapter {TYPE_2__ halmac_state; } ;
typedef  enum halmac_scan_cmd_construct_state { ____Placeholder_halmac_scan_cmd_construct_state } halmac_scan_cmd_construct_state ;

/* Variables and functions */

enum halmac_scan_cmd_construct_state
halmac_query_scan_curr_state_88xx(struct halmac_adapter *halmac_adapter)
{
	return halmac_adapter->halmac_state.scan_state_set
		.scan_cmd_construct_state;
}
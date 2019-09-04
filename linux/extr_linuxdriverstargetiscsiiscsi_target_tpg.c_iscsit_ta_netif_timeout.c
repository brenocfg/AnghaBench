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
typedef  scalar_t__ u32 ;
struct iscsi_tpg_attrib {scalar_t__ netif_timeout; } ;
struct iscsi_portal_group {int /*<<< orphan*/  tpgt; struct iscsi_tpg_attrib tpg_attrib; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TA_NETIF_TIMEOUT_MAX ; 
 scalar_t__ TA_NETIF_TIMEOUT_MIN ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 

int iscsit_ta_netif_timeout(
	struct iscsi_portal_group *tpg,
	u32 netif_timeout)
{
	struct iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	if (netif_timeout > TA_NETIF_TIMEOUT_MAX) {
		pr_err("Requested Network Interface Timeout %u larger"
			" than maximum %u\n", netif_timeout,
				TA_NETIF_TIMEOUT_MAX);
		return -EINVAL;
	} else if (netif_timeout < TA_NETIF_TIMEOUT_MIN) {
		pr_err("Requested Network Interface Timeout %u smaller"
			" than minimum %u\n", netif_timeout,
				TA_NETIF_TIMEOUT_MIN);
		return -EINVAL;
	}

	a->netif_timeout = netif_timeout;
	pr_debug("Set Network Interface Timeout to %u for"
		" Target Portal Group %hu\n", a->netif_timeout, tpg->tpgt);

	return 0;
}
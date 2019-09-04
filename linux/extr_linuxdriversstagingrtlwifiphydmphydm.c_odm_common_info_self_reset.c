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
struct TYPE_2__ {scalar_t__ num_qry_beacon_pkt; } ;
struct phy_dm_struct {TYPE_1__ phy_dbg_info; } ;

/* Variables and functions */

__attribute__((used)) static void odm_common_info_self_reset(struct phy_dm_struct *dm)
{
	dm->phy_dbg_info.num_qry_beacon_pkt = 0;
}
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
struct txpwrtrack_cfg {int dummy; } ;
struct phy_dm_struct {scalar_t__ support_ic_type; } ;

/* Variables and functions */
 scalar_t__ ODM_RTL8822B ; 
 int /*<<< orphan*/  configure_txpower_track_8822b (struct txpwrtrack_cfg*) ; 

void configure_txpower_track(void *dm_void, struct txpwrtrack_cfg *config)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	/* JJ ADD 20161014 */

	if (dm->support_ic_type == ODM_RTL8822B)
		configure_txpower_track_8822b(config);
}
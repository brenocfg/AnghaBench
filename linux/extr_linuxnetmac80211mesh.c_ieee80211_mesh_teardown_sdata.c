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
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mesh_pathtbl_unregister (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mesh_rmc_free (struct ieee80211_sub_if_data*) ; 

void ieee80211_mesh_teardown_sdata(struct ieee80211_sub_if_data *sdata)
{
	mesh_rmc_free(sdata);
	mesh_pathtbl_unregister(sdata);
}
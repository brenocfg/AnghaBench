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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  mesh_paths_generation; int /*<<< orphan*/  mesh_paths; } ;
struct TYPE_4__ {TYPE_1__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpp_flush_by_proxy (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 int table_path_del (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 

int mesh_path_del(struct ieee80211_sub_if_data *sdata, const u8 *addr)
{
	int err;

	/* flush relevant mpp entries first */
	mpp_flush_by_proxy(sdata, addr);

	err = table_path_del(sdata->u.mesh.mesh_paths, sdata, addr);
	sdata->u.mesh.mesh_paths_generation++;
	return err;
}
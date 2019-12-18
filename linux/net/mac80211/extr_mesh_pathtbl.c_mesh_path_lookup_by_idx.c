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
struct mesh_path {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mesh_paths; } ;
struct TYPE_4__ {TYPE_1__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;

/* Variables and functions */
 struct mesh_path* __mesh_path_lookup_by_idx (int /*<<< orphan*/ ,int) ; 

struct mesh_path *
mesh_path_lookup_by_idx(struct ieee80211_sub_if_data *sdata, int idx)
{
	return __mesh_path_lookup_by_idx(sdata->u.mesh.mesh_paths, idx);
}
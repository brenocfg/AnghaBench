#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ieee80211_mesh_sync_ops {int dummy; } ;
struct TYPE_3__ {scalar_t__ method; struct ieee80211_mesh_sync_ops const ops; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* sync_methods ; 

const struct ieee80211_mesh_sync_ops *ieee80211_mesh_sync_ops_get(u8 method)
{
	int i;

	for (i = 0 ; i < ARRAY_SIZE(sync_methods); ++i) {
		if (sync_methods[i].method == method)
			return &sync_methods[i].ops;
	}
	return NULL;
}
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
struct obs_hotkey_internal_find_forward {scalar_t__ id; size_t idx; int found; } ;
struct TYPE_3__ {scalar_t__ id; } ;
typedef  TYPE_1__ obs_hotkey_t ;

/* Variables and functions */

__attribute__((used)) static inline bool find_id_helper(void *data, size_t idx, obs_hotkey_t *hotkey)
{
	struct obs_hotkey_internal_find_forward *find = data;
	if (hotkey->id != find->id)
		return true;

	find->idx   = idx;
	find->found = true;
	return false;
}
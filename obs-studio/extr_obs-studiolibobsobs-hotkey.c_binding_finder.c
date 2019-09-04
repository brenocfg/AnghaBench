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
struct binding_find_data {scalar_t__ id; size_t* idx; int found; } ;
struct TYPE_3__ {scalar_t__ hotkey_id; } ;
typedef  TYPE_1__ obs_hotkey_binding_t ;

/* Variables and functions */

__attribute__((used)) static inline bool binding_finder(void *data,
		size_t idx, obs_hotkey_binding_t *binding)
{
	struct binding_find_data *find = data;
	if (binding->hotkey_id != find->id)
		return true;

	*find->idx  = idx;
	find->found = true;
	return false;
}
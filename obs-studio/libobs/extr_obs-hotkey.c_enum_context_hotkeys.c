#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num; int /*<<< orphan*/ * array; } ;
struct obs_context_data {TYPE_1__ hotkeys; } ;
typedef  int /*<<< orphan*/  obs_hotkey_t ;
typedef  int /*<<< orphan*/  (* obs_hotkey_internal_enum_func ) (void*,size_t,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  obs_hotkey_id ;
struct TYPE_6__ {int /*<<< orphan*/ * array; } ;
struct TYPE_7__ {TYPE_2__ hotkeys; } ;
struct TYPE_8__ {TYPE_3__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_id (int /*<<< orphan*/  const,size_t*) ; 
 TYPE_4__* obs ; 

__attribute__((used)) static inline void enum_context_hotkeys(struct obs_context_data *context,
					obs_hotkey_internal_enum_func func,
					void *data)
{
	const size_t num = context->hotkeys.num;
	const obs_hotkey_id *array = context->hotkeys.array;
	obs_hotkey_t *hotkey_array = obs->hotkeys.hotkeys.array;
	for (size_t i = 0; i < num; i++) {
		size_t idx;
		if (!find_id(array[i], &idx))
			continue;

		if (!func(data, idx, &hotkey_array[idx]))
			break;
	}
}
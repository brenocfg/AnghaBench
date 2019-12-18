#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct obs_context_data {int /*<<< orphan*/  hotkey_pairs; } ;
struct TYPE_8__ {scalar_t__ pair_id; void** data; void** id; void** func; } ;
typedef  TYPE_2__ obs_hotkey_pair_t ;
typedef  void* obs_hotkey_active_func ;
struct TYPE_10__ {TYPE_2__* array; } ;
struct TYPE_7__ {scalar_t__ next_pair_id; TYPE_5__ hotkey_pairs; } ;
struct TYPE_9__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 void* OBS_INVALID_HOTKEY_ID ; 
 scalar_t__ OBS_INVALID_HOTKEY_PAIR_ID ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_2__* da_push_back_new (TYPE_5__) ; 
 int /*<<< orphan*/  fixup_pair_pointers () ; 
 TYPE_3__* obs ; 

__attribute__((used)) static obs_hotkey_pair_t *create_hotkey_pair(struct obs_context_data *context,
					     obs_hotkey_active_func func0,
					     obs_hotkey_active_func func1,
					     void *data0, void *data1)
{
	if ((obs->hotkeys.next_pair_id + 1) == OBS_INVALID_HOTKEY_PAIR_ID)
		blog(LOG_WARNING, "obs-hotkey: Available hotkey pair ids "
				  "exhausted");

	obs_hotkey_pair_t *base_addr = obs->hotkeys.hotkey_pairs.array;
	obs_hotkey_pair_t *pair = da_push_back_new(obs->hotkeys.hotkey_pairs);

	pair->pair_id = obs->hotkeys.next_pair_id++;
	pair->func[0] = func0;
	pair->func[1] = func1;
	pair->id[0] = OBS_INVALID_HOTKEY_ID;
	pair->id[1] = OBS_INVALID_HOTKEY_ID;
	pair->data[0] = data0;
	pair->data[1] = data1;

	if (context)
		da_push_back(context->hotkey_pairs, &pair->pair_id);

	if (base_addr != obs->hotkeys.hotkey_pairs.array)
		fixup_pair_pointers();

	return pair;
}
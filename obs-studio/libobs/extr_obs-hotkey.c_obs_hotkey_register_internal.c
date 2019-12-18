#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct obs_context_data {int /*<<< orphan*/  hotkey_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  pair_partner_id; void* registerer; int /*<<< orphan*/  registerer_type; void* data; int /*<<< orphan*/  func; void* description; void* name; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ obs_hotkey_t ;
typedef  int /*<<< orphan*/  obs_hotkey_registerer_t ;
typedef  int /*<<< orphan*/  obs_hotkey_id ;
typedef  int /*<<< orphan*/  obs_hotkey_func ;
typedef  int /*<<< orphan*/  obs_data_array_t ;
struct TYPE_11__ {TYPE_2__* array; } ;
struct TYPE_8__ {scalar_t__ next_id; TYPE_7__ hotkeys; } ;
struct TYPE_10__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ OBS_INVALID_HOTKEY_ID ; 
 int /*<<< orphan*/  OBS_INVALID_HOTKEY_PAIR_ID ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 void* bstrdup (char const*) ; 
 int /*<<< orphan*/  context_add_hotkey (struct obs_context_data*,int /*<<< orphan*/ ) ; 
 TYPE_2__* da_push_back_new (TYPE_7__) ; 
 int /*<<< orphan*/  fixup_pointers () ; 
 int /*<<< orphan*/  hotkey_signal (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  load_bindings (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* obs ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_get_array (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline obs_hotkey_id
obs_hotkey_register_internal(obs_hotkey_registerer_t type, void *registerer,
			     struct obs_context_data *context, const char *name,
			     const char *description, obs_hotkey_func func,
			     void *data)
{
	if ((obs->hotkeys.next_id + 1) == OBS_INVALID_HOTKEY_ID)
		blog(LOG_WARNING, "obs-hotkey: Available hotkey ids exhausted");

	obs_hotkey_t *base_addr = obs->hotkeys.hotkeys.array;
	obs_hotkey_id result = obs->hotkeys.next_id++;
	obs_hotkey_t *hotkey = da_push_back_new(obs->hotkeys.hotkeys);

	hotkey->id = result;
	hotkey->name = bstrdup(name);
	hotkey->description = bstrdup(description);
	hotkey->func = func;
	hotkey->data = data;
	hotkey->registerer_type = type;
	hotkey->registerer = registerer;
	hotkey->pair_partner_id = OBS_INVALID_HOTKEY_PAIR_ID;

	if (context) {
		obs_data_array_t *data =
			obs_data_get_array(context->hotkey_data, name);
		load_bindings(hotkey, data);
		obs_data_array_release(data);

		context_add_hotkey(context, result);
	}

	if (base_addr != obs->hotkeys.hotkeys.array)
		fixup_pointers();

	hotkey_signal("hotkey_register", hotkey);

	return result;
}
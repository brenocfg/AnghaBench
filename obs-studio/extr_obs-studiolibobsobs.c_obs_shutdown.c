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
struct obs_source_info {scalar_t__ type_data; int /*<<< orphan*/  (* free_type_data ) (scalar_t__) ;} ;
struct obs_service_info {scalar_t__ type_data; int /*<<< orphan*/  (* free_type_data ) (scalar_t__) ;} ;
struct obs_output_info {scalar_t__ type_data; int /*<<< orphan*/  (* free_type_data ) (scalar_t__) ;} ;
struct obs_module {struct obs_module* next; } ;
struct obs_modeless_ui {scalar_t__ type_data; int /*<<< orphan*/  (* free_type_data ) (scalar_t__) ;} ;
struct obs_modal_ui {scalar_t__ type_data; int /*<<< orphan*/  (* free_type_data ) (scalar_t__) ;} ;
struct obs_encoder_info {scalar_t__ type_data; int /*<<< orphan*/  (* free_type_data ) (scalar_t__) ;} ;
struct TYPE_3__ {size_t num; struct obs_source_info* array; } ;
struct obs_core {struct obs_core* locale; struct obs_core* module_config_path; int /*<<< orphan*/  name_store; scalar_t__ name_store_owned; TYPE_1__ module_paths; struct obs_module* first_module; int /*<<< orphan*/ * signals; int /*<<< orphan*/ * procs; TYPE_1__ transition_types; TYPE_1__ filter_types; TYPE_1__ input_types; TYPE_1__ modeless_ui_callbacks; TYPE_1__ modal_ui_callbacks; TYPE_1__ service_types; TYPE_1__ encoder_types; TYPE_1__ output_types; TYPE_1__ source_types; } ;
struct TYPE_4__ {struct obs_core* argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct obs_core*) ; 
 TYPE_2__ cmdline_args ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  free_module (struct obs_module*) ; 
 int /*<<< orphan*/  free_module_path (struct obs_source_info*) ; 
 struct obs_core* obs ; 
 int /*<<< orphan*/  obs_free_audio () ; 
 int /*<<< orphan*/  obs_free_data () ; 
 int /*<<< orphan*/  obs_free_graphics () ; 
 int /*<<< orphan*/  obs_free_hotkeys () ; 
 int /*<<< orphan*/  obs_free_video () ; 
 int /*<<< orphan*/  proc_handler_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profiler_name_store_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_hotkeys () ; 
 int /*<<< orphan*/  stop_video () ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 int /*<<< orphan*/  stub5 (scalar_t__) ; 
 int /*<<< orphan*/  stub6 (scalar_t__) ; 

void obs_shutdown(void)
{
	struct obs_module *module;
	struct obs_core *core;

	if (!obs)
		return;

#define FREE_REGISTERED_TYPES(structure, list) \
	do { \
		for (size_t i = 0; i < list.num; i++) { \
			struct structure *item = &list.array[i]; \
			if (item->type_data && item->free_type_data) \
				item->free_type_data(item->type_data); \
		} \
		da_free(list); \
	} while (false)

	FREE_REGISTERED_TYPES(obs_source_info, obs->source_types);
	FREE_REGISTERED_TYPES(obs_output_info, obs->output_types);
	FREE_REGISTERED_TYPES(obs_encoder_info, obs->encoder_types);
	FREE_REGISTERED_TYPES(obs_service_info, obs->service_types);
	FREE_REGISTERED_TYPES(obs_modal_ui, obs->modal_ui_callbacks);
	FREE_REGISTERED_TYPES(obs_modeless_ui, obs->modeless_ui_callbacks);

#undef FREE_REGISTERED_TYPES

	da_free(obs->input_types);
	da_free(obs->filter_types);
	da_free(obs->transition_types);

	stop_video();
	stop_hotkeys();

	obs_free_audio();
	obs_free_data();
	obs_free_video();
	obs_free_hotkeys();
	obs_free_graphics();
	proc_handler_destroy(obs->procs);
	signal_handler_destroy(obs->signals);
	obs->procs = NULL;
	obs->signals = NULL;

	core = obs;
	obs = NULL;

	module = core->first_module;
	while (module) {
		struct obs_module *next = module->next;
		free_module(module);
		module = next;
	}
	core->first_module = NULL;

	for (size_t i = 0; i < core->module_paths.num; i++)
		free_module_path(core->module_paths.array+i);
	da_free(core->module_paths);

	if (core->name_store_owned)
		profiler_name_store_free(core->name_store);

	bfree(core->module_config_path);
	bfree(core->locale);
	bfree(core);
	bfree(cmdline_args.argv);

#ifdef _WIN32
	uninitialize_com();
#endif
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct calldata {int dummy; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  signals; int /*<<< orphan*/  private; } ;
struct TYPE_7__ {TYPE_4__ context; } ;
typedef  TYPE_1__ obs_source_t ;
struct TYPE_9__ {int /*<<< orphan*/  signals; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 char* bstrdup (char*) ; 
 int /*<<< orphan*/  calldata_free (struct calldata*) ; 
 int /*<<< orphan*/  calldata_init (struct calldata*) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  calldata_set_string (struct calldata*,char*,char*) ; 
 TYPE_5__* obs ; 
 int /*<<< orphan*/  obs_context_data_setname (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void obs_source_set_name(obs_source_t *source, const char *name)
{
	if (!obs_source_valid(source, "obs_source_set_name"))
		return;

	if (!name || !*name || !source->context.name ||
	    strcmp(name, source->context.name) != 0) {
		struct calldata data;
		char *prev_name = bstrdup(source->context.name);
		obs_context_data_setname(&source->context, name);

		calldata_init(&data);
		calldata_set_ptr(&data, "source", source);
		calldata_set_string(&data, "new_name", source->context.name);
		calldata_set_string(&data, "prev_name", prev_name);
		if (!source->context.private)
			signal_handler_signal(obs->signals, "source_rename",
					      &data);
		signal_handler_signal(source->context.signals, "rename", &data);
		calldata_free(&data);
		bfree(prev_name);
	}
}
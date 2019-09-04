#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct obs_context_data {TYPE_1__ hotkeys; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  enum_context_hotkeys (struct obs_context_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enum_save_hotkey ; 
 int /*<<< orphan*/ * obs_data_create () ; 

__attribute__((used)) static inline obs_data_t *save_context_hotkeys(struct obs_context_data *context)
{
	if (!context->hotkeys.num)
		return NULL;

	obs_data_t *result = obs_data_create();
	enum_context_hotkeys(context, enum_save_hotkey, result);
	return result;
}
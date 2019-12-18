#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  (* enum_active_sources ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;
struct TYPE_11__ {TYPE_1__ context; TYPE_2__ info; } ;
typedef  TYPE_3__ obs_source_t ;
typedef  int /*<<< orphan*/  obs_source_enum_proc_t ;

/* Variables and functions */
 scalar_t__ OBS_SOURCE_TYPE_TRANSITION ; 
 int /*<<< orphan*/  data_valid (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  obs_source_addref (TYPE_3__*) ; 
 int /*<<< orphan*/  obs_source_release (TYPE_3__*) ; 
 int /*<<< orphan*/  obs_transition_enum_sources (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void obs_source_enum_active_sources(obs_source_t *source,
				    obs_source_enum_proc_t enum_callback,
				    void *param)
{
	bool is_transition;
	if (!data_valid(source, "obs_source_enum_active_sources"))
		return;

	is_transition = source->info.type == OBS_SOURCE_TYPE_TRANSITION;
	if (!is_transition && !source->info.enum_active_sources)
		return;

	obs_source_addref(source);

	if (is_transition)
		obs_transition_enum_sources(source, enum_callback, param);
	if (source->info.enum_active_sources)
		source->info.enum_active_sources(source->context.data,
						 enum_callback, param);

	obs_source_release(source);
}
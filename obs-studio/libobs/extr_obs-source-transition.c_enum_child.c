#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* enum_active_sources ) (scalar_t__,int /*<<< orphan*/  (*) (TYPE_3__*,TYPE_3__*,void*),void*) ;} ;
struct TYPE_14__ {TYPE_2__ context; TYPE_1__ info; } ;
typedef  TYPE_3__ obs_source_t ;
typedef  int /*<<< orphan*/  (* obs_source_enum_proc_t ) (TYPE_3__*,TYPE_3__*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/  (*) (TYPE_3__*,TYPE_3__*,void*),void*) ; 

__attribute__((used)) static inline void enum_child(obs_source_t *tr, obs_source_t *child,
			      obs_source_enum_proc_t enum_callback, void *param)
{
	if (!child)
		return;

	if (child->context.data && child->info.enum_active_sources)
		child->info.enum_active_sources(child->context.data,
						enum_callback, param);

	enum_callback(tr, child, param);
}
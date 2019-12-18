#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ obs_weak_source_t ;
struct TYPE_7__ {TYPE_1__* control; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  obs ; 
 scalar_t__ obs_ref_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_weak_source_release (TYPE_1__*) ; 

void obs_source_release(obs_source_t *source)
{
	if (!obs) {
		blog(LOG_WARNING, "Tried to release a source when the OBS "
				  "core is shut down!");
		return;
	}

	if (!source)
		return;

	obs_weak_source_t *control = source->control;
	if (obs_ref_release(&control->ref)) {
		obs_source_destroy(source);
		obs_weak_source_release(control);
	}
}
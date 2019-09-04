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
struct obs_module_path {int dummy; } ;
typedef  int /*<<< orphan*/  obs_find_module_callback_t ;
struct TYPE_3__ {size_t num; struct obs_module_path* array; } ;
struct TYPE_4__ {TYPE_1__ module_paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_modules_in_path (struct obs_module_path*,int /*<<< orphan*/ ,void*) ; 
 TYPE_2__* obs ; 

void obs_find_modules(obs_find_module_callback_t callback, void *param)
{
	if (!obs)
		return;

	for (size_t i = 0; i < obs->module_paths.num; i++) {
		struct obs_module_path *omp = obs->module_paths.array + i;
		find_modules_in_path(omp, callback, param);
	}
}
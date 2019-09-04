#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gs_sparam_t ;
typedef  int /*<<< orphan*/  gs_shader_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* gs_shader_get_param_by_name ) (int /*<<< orphan*/ *,char const*) ;} ;
struct TYPE_5__ {TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid_p2 (char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* thread_graphics ; 

gs_sparam_t *gs_shader_get_param_by_name(gs_shader_t *shader, const char *name)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid_p2("gs_shader_get_param_by_name", shader, name))
		return NULL;

	return graphics->exports.gs_shader_get_param_by_name(shader, name);
}
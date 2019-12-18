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
struct TYPE_4__ {int /*<<< orphan*/ * (* gs_shader_get_world_matrix ) (int /*<<< orphan*/  const*) ;} ;
struct TYPE_5__ {TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid_p (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/  const*) ; 
 TYPE_2__* thread_graphics ; 

gs_sparam_t *gs_shader_get_world_matrix(const gs_shader_t *shader)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid_p("gs_shader_get_world_matrix", shader))
		return NULL;

	return graphics->exports.gs_shader_get_world_matrix(shader);
}
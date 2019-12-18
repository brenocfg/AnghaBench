#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct gs_effect {struct gs_effect* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* device_destroy ) (scalar_t__) ;int /*<<< orphan*/  (* gs_vertexbuffer_destroy ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* device_enter_context ) (scalar_t__) ;} ;
struct TYPE_8__ {scalar_t__ module; int /*<<< orphan*/  blend_state_stack; int /*<<< orphan*/  viewport_stack; int /*<<< orphan*/  matrix_stack; int /*<<< orphan*/  effect_mutex; int /*<<< orphan*/  mutex; scalar_t__ device; TYPE_1__ exports; int /*<<< orphan*/  immediate_vertbuffer; int /*<<< orphan*/  sprite_buffer; struct gs_effect* first_effect; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_2__*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_actually_destroy (struct gs_effect*) ; 
 int /*<<< orphan*/  gs_free_image_deps () ; 
 int /*<<< orphan*/  gs_leave_context () ; 
 int /*<<< orphan*/  os_dlclose (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (scalar_t__) ; 
 TYPE_2__* thread_graphics ; 

void gs_destroy(graphics_t *graphics)
{
	if (!ptr_valid(graphics, "gs_destroy"))
		return;

	while (thread_graphics)
		gs_leave_context();

	if (graphics->device) {
		struct gs_effect *effect = graphics->first_effect;

		thread_graphics = graphics;
		graphics->exports.device_enter_context(graphics->device);

		while (effect) {
			struct gs_effect *next = effect->next;
			gs_effect_actually_destroy(effect);
			effect = next;
		}

		graphics->exports.gs_vertexbuffer_destroy(
			graphics->sprite_buffer);
		graphics->exports.gs_vertexbuffer_destroy(
			graphics->immediate_vertbuffer);
		graphics->exports.device_destroy(graphics->device);

		thread_graphics = NULL;
	}

	pthread_mutex_destroy(&graphics->mutex);
	pthread_mutex_destroy(&graphics->effect_mutex);
	da_free(graphics->matrix_stack);
	da_free(graphics->viewport_stack);
	da_free(graphics->blend_state_stack);
	if (graphics->module)
		os_dlclose(graphics->module);
	bfree(graphics);

	gs_free_image_deps();
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cur_matrix; int /*<<< orphan*/  matrix_stack; } ;
typedef  TYPE_1__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  da_erase (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 TYPE_1__* thread_graphics ; 

void gs_matrix_pop(void)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_matrix_pop"))
		return;

	if (graphics->cur_matrix == 0) {
		blog(LOG_ERROR, "Tried to pop last matrix on stack");
		return;
	}

	da_erase(graphics->matrix_stack, graphics->cur_matrix);
	graphics->cur_matrix--;
}
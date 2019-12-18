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
struct gs_rect {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  viewport_stack; } ;

/* Variables and functions */
 struct gs_rect* da_push_back_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_get_viewport (struct gs_rect*) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 TYPE_1__* thread_graphics ; 

void gs_viewport_push(void)
{
	if (!gs_valid("gs_viewport_push"))
		return;

	struct gs_rect *rect =
		da_push_back_new(thread_graphics->viewport_stack);
	gs_get_viewport(rect);
}
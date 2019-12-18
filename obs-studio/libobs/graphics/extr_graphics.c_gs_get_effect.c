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
typedef  int /*<<< orphan*/  gs_effect_t ;
struct TYPE_2__ {int /*<<< orphan*/ * cur_effect; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid (char*) ; 
 TYPE_1__* thread_graphics ; 

gs_effect_t *gs_get_effect(void)
{
	if (!gs_valid("gs_get_effect"))
		return NULL;

	return thread_graphics ? thread_graphics->cur_effect : NULL;
}
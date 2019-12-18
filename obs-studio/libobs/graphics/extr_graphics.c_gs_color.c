#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  num; } ;
struct TYPE_5__ {TYPE_4__ colors; } ;
typedef  TYPE_1__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (TYPE_4__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 TYPE_1__* thread_graphics ; 
 int /*<<< orphan*/  validvertsize (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

void gs_color(uint32_t color)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_color"))
		return;
	if (!validvertsize(graphics, graphics->colors.num, "gs_color"))
		return;

	da_push_back(graphics->colors, &color);
}
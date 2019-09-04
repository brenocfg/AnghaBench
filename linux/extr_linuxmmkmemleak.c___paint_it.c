#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kmemleak_object {int min_count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int KMEMLEAK_BLACK ; 
 int /*<<< orphan*/  OBJECT_NO_SCAN ; 

__attribute__((used)) static void __paint_it(struct kmemleak_object *object, int color)
{
	object->min_count = color;
	if (color == KMEMLEAK_BLACK)
		object->flags |= OBJECT_NO_SCAN;
}
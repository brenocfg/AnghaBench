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
struct kmemleak_object {int /*<<< orphan*/  gray_list; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ color_gray (struct kmemleak_object*) ; 
 int /*<<< orphan*/  color_white (struct kmemleak_object*) ; 
 int /*<<< orphan*/  get_object (struct kmemleak_object*) ; 
 int /*<<< orphan*/  gray_list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_refs(struct kmemleak_object *object)
{
	if (!color_white(object)) {
		/* non-orphan, ignored or new */
		return;
	}

	/*
	 * Increase the object's reference count (number of pointers to the
	 * memory block). If this count reaches the required minimum, the
	 * object's color will become gray and it will be added to the
	 * gray_list.
	 */
	object->count++;
	if (color_gray(object)) {
		/* put_object() called when removing from gray_list */
		WARN_ON(!get_object(object));
		list_add_tail(&object->gray_list, &gray_list);
	}
}
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
struct debug_obj {int dummy; } ;

/* Variables and functions */
 scalar_t__ __free_object (struct debug_obj*) ; 
 int /*<<< orphan*/  debug_obj_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_object(struct debug_obj *obj)
{
	if (__free_object(obj))
		schedule_work(&debug_obj_work);
}
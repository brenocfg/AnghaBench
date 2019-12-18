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
struct klp_object {struct klp_object* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct klp_object*) ; 

__attribute__((used)) static void klp_free_object_dynamic(struct klp_object *obj)
{
	kfree(obj->name);
	kfree(obj);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* value; struct TYPE_4__* name; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ param_prop_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_prop(param_prop_t *prop)
{
    list_remove(&prop->entry);

    heap_free(prop->name);
    heap_free(prop->value);
    heap_free(prop);
}
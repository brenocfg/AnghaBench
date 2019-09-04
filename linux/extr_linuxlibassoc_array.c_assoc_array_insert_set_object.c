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
struct assoc_array_edit {int /*<<< orphan*/  leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  assoc_array_leaf_to_ptr (void*) ; 

void assoc_array_insert_set_object(struct assoc_array_edit *edit, void *object)
{
	BUG_ON(!object);
	edit->leaf = assoc_array_leaf_to_ptr(object);
}
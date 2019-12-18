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
struct assoc_array_ops {int dummy; } ;
struct assoc_array {int /*<<< orphan*/ * root; } ;

/* Variables and functions */
 int /*<<< orphan*/  assoc_array_destroy_subtree (int /*<<< orphan*/ *,struct assoc_array_ops const*) ; 

void assoc_array_destroy(struct assoc_array *array,
			 const struct assoc_array_ops *ops)
{
	assoc_array_destroy_subtree(array->root, ops);
	array->root = NULL;
}
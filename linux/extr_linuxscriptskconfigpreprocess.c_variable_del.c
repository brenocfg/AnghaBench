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
struct variable {struct variable* value; struct variable* name; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct variable*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void variable_del(struct variable *v)
{
	list_del(&v->node);
	free(v->name);
	free(v->value);
	free(v);
}
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
struct env {struct env* value; struct env* name; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct env*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void env_del(struct env *e)
{
	list_del(&e->node);
	free(e->name);
	free(e->value);
	free(e);
}
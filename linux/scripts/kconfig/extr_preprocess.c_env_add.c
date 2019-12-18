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
struct env {int /*<<< orphan*/  node; void* value; void* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  env_list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct env* xmalloc (int) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static void env_add(const char *name, const char *value)
{
	struct env *e;

	e = xmalloc(sizeof(*e));
	e->name = xstrdup(name);
	e->value = xstrdup(value);

	list_add_tail(&e->node, &env_list);
}
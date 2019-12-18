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
struct variable {struct variable* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecpg_free (struct variable*) ; 

__attribute__((used)) static void
free_variable(struct variable *var)
{
	struct variable *var_next;

	while (var)
	{
		var_next = var->next;
		ecpg_free(var);
		var = var_next;
	}
}
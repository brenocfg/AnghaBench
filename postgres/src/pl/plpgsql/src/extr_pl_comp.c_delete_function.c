#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ use_count; } ;
typedef  TYPE_1__ PLpgSQL_function ;

/* Variables and functions */
 int /*<<< orphan*/  plpgsql_HashTableDelete (TYPE_1__*) ; 
 int /*<<< orphan*/  plpgsql_free_function_memory (TYPE_1__*) ; 

__attribute__((used)) static void
delete_function(PLpgSQL_function *func)
{
	/* remove function from hash table (might be done already) */
	plpgsql_HashTableDelete(func);

	/* release the function's storage if safe and not done already */
	if (func->use_count == 0)
		plpgsql_free_function_memory(func);
}
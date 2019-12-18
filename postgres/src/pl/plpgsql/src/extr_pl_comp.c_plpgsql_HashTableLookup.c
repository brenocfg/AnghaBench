#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * function; } ;
typedef  TYPE_1__ plpgsql_HashEnt ;
typedef  int /*<<< orphan*/  PLpgSQL_function ;
typedef  int /*<<< orphan*/  PLpgSQL_func_hashkey ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plpgsql_HashTable ; 

__attribute__((used)) static PLpgSQL_function *
plpgsql_HashTableLookup(PLpgSQL_func_hashkey *func_key)
{
	plpgsql_HashEnt *hentry;

	hentry = (plpgsql_HashEnt *) hash_search(plpgsql_HashTable,
											 (void *) func_key,
											 HASH_FIND,
											 NULL);
	if (hentry)
		return hentry->function;
	else
		return NULL;
}
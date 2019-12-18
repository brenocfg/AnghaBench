#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  key; TYPE_2__* function; } ;
typedef  TYPE_1__ plpgsql_HashEnt ;
struct TYPE_5__ {int /*<<< orphan*/ * fn_hashkey; } ;
typedef  TYPE_2__ PLpgSQL_function ;
typedef  int /*<<< orphan*/  PLpgSQL_func_hashkey ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  plpgsql_HashTable ; 

__attribute__((used)) static void
plpgsql_HashTableInsert(PLpgSQL_function *function,
						PLpgSQL_func_hashkey *func_key)
{
	plpgsql_HashEnt *hentry;
	bool		found;

	hentry = (plpgsql_HashEnt *) hash_search(plpgsql_HashTable,
											 (void *) func_key,
											 HASH_ENTER,
											 &found);
	if (found)
		elog(WARNING, "trying to insert a function that already exists");

	hentry->function = function;
	/* prepare back link from function to hashtable key */
	function->fn_hashkey = &hentry->key;
}
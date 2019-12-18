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
struct TYPE_4__ {int /*<<< orphan*/  find_locked; } ;
typedef  TYPE_1__ dshash_table ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

void
dshash_detach(dshash_table *hash_table)
{
	Assert(!hash_table->find_locked);

	/* The hash table may have been destroyed.  Just free local memory. */
	pfree(hash_table);
}
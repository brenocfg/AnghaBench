#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  additional; } ;
struct TYPE_6__ {int num_hashes; int /*<<< orphan*/ * hash_pergroup; } ;
typedef  int /*<<< orphan*/  AggStatePerGroup ;
typedef  TYPE_1__ AggState ;

/* Variables and functions */
 TYPE_3__* lookup_hash_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  select_current_set (TYPE_1__*,int,int) ; 

__attribute__((used)) static void
lookup_hash_entries(AggState *aggstate)
{
	int			numHashes = aggstate->num_hashes;
	AggStatePerGroup *pergroup = aggstate->hash_pergroup;
	int			setno;

	for (setno = 0; setno < numHashes; setno++)
	{
		select_current_set(aggstate, setno, true);
		pergroup[setno] = lookup_hash_entry(aggstate)->additional;
	}
}
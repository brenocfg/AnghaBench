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
typedef  int /*<<< orphan*/  dsa_pointer ;
struct TYPE_4__ {int /*<<< orphan*/ * shared; } ;
struct TYPE_5__ {int /*<<< orphan*/  area; TYPE_1__ buckets; int /*<<< orphan*/  parallel_state; } ;
typedef  scalar_t__ HashJoinTuple ;
typedef  TYPE_2__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_pointer_atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline HashJoinTuple
ExecParallelHashFirstTuple(HashJoinTable hashtable, int bucketno)
{
	HashJoinTuple tuple;
	dsa_pointer p;

	Assert(hashtable->parallel_state);
	p = dsa_pointer_atomic_read(&hashtable->buckets.shared[bucketno]);
	tuple = (HashJoinTuple) dsa_get_address(hashtable->area, p);

	return tuple;
}
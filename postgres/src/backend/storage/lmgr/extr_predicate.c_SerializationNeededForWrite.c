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
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 scalar_t__ InvalidSerializableXact ; 
 scalar_t__ MySerializableXact ; 
 int /*<<< orphan*/  PredicateLockingNeededForRelation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
SerializationNeededForWrite(Relation relation)
{
	/* Nothing to do if this is not a serializable transaction */
	if (MySerializableXact == InvalidSerializableXact)
		return false;

	/* Check if the relation doesn't participate in predicate locking */
	if (!PredicateLockingNeededForRelation(relation))
		return false;

	return true;				/* no excuse to skip predicate locking */
}
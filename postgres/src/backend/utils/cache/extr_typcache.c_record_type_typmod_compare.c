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
struct TYPE_2__ {int /*<<< orphan*/  tupdesc; } ;
typedef  TYPE_1__ RecordCacheEntry ;

/* Variables and functions */
 scalar_t__ equalTupleDescs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
record_type_typmod_compare(const void *a, const void *b, size_t size)
{
	RecordCacheEntry *left = (RecordCacheEntry *) a;
	RecordCacheEntry *right = (RecordCacheEntry *) b;

	return equalTupleDescs(left->tupdesc, right->tupdesc) ? 0 : 1;
}
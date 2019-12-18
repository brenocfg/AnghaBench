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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_2__ {int /*<<< orphan*/  tupdesc; } ;
typedef  TYPE_1__ RecordCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  hashTupleDesc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
record_type_typmod_hash(const void *data, size_t size)
{
	RecordCacheEntry *entry = (RecordCacheEntry *) data;

	return hashTupleDesc(entry->tupdesc);
}
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
struct TYPE_2__ {int id; } ;
typedef  int /*<<< orphan*/  BufferTag ;
typedef  TYPE_1__ BufferLookupEnt ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  SharedBufHash ; 
 scalar_t__ hash_search_with_hash_value (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
BufTableLookup(BufferTag *tagPtr, uint32 hashcode)
{
	BufferLookupEnt *result;

	result = (BufferLookupEnt *)
		hash_search_with_hash_value(SharedBufHash,
									(void *) tagPtr,
									hashcode,
									HASH_FIND,
									NULL);

	if (!result)
		return -1;

	return result->id;
}
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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_5__ {int id; } ;
struct TYPE_4__ {scalar_t__ blockNum; } ;
typedef  TYPE_1__ BufferTag ;
typedef  TYPE_2__ BufferLookupEnt ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 scalar_t__ P_NEW ; 
 int /*<<< orphan*/  SharedBufHash ; 
 scalar_t__ hash_search_with_hash_value (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
BufTableInsert(BufferTag *tagPtr, uint32 hashcode, int buf_id)
{
	BufferLookupEnt *result;
	bool		found;

	Assert(buf_id >= 0);		/* -1 is reserved for not-in-table */
	Assert(tagPtr->blockNum != P_NEW);	/* invalid tag */

	result = (BufferLookupEnt *)
		hash_search_with_hash_value(SharedBufHash,
									(void *) tagPtr,
									hashcode,
									HASH_ENTER,
									&found);

	if (found)					/* found something already in the table */
		return result->id;

	result->id = buf_id;

	return -1;
}
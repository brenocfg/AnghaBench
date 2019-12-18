#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_7__ {scalar_t__ t_len; scalar_t__ t_data; } ;
struct TYPE_6__ {scalar_t__ t_len; } ;
typedef  TYPE_1__* MinimalTuple ;
typedef  TYPE_2__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MINIMAL_TUPLE_OFFSET ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char*,scalar_t__) ; 
 scalar_t__ palloc (scalar_t__) ; 

MinimalTuple
minimal_tuple_from_heap_tuple(HeapTuple htup)
{
	MinimalTuple result;
	uint32		len;

	Assert(htup->t_len > MINIMAL_TUPLE_OFFSET);
	len = htup->t_len - MINIMAL_TUPLE_OFFSET;
	result = (MinimalTuple) palloc(len);
	memcpy(result, (char *) htup->t_data + MINIMAL_TUPLE_OFFSET, len);
	result->t_len = len;
	return result;
}
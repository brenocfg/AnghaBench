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
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  scalar_t__ MinimalTuple ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  GetMemoryChunkSpace (scalar_t__) ; 
 int /*<<< orphan*/  USEMEM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ minimal_tuple_from_heap_tuple (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
copytup_heap(Tuplestorestate *state, void *tup)
{
	MinimalTuple tuple;

	tuple = minimal_tuple_from_heap_tuple((HeapTuple) tup);
	USEMEM(state, GetMemoryChunkSpace(tuple));
	return (void *) tuple;
}
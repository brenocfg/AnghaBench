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
typedef  int uint64 ;
typedef  int /*<<< orphan*/  ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int GinItemPointerGetBlockNumber (int /*<<< orphan*/  const) ; 
 int GinItemPointerGetOffsetNumber (int /*<<< orphan*/  const) ; 
 int ItemPointerIsValid (int /*<<< orphan*/  const) ; 
 int MaxHeapTuplesPerPageBits ; 

__attribute__((used)) static inline uint64
itemptr_to_uint64(const ItemPointer iptr)
{
	uint64		val;

	Assert(ItemPointerIsValid(iptr));
	Assert(GinItemPointerGetOffsetNumber(iptr) < (1 << MaxHeapTuplesPerPageBits));

	val = GinItemPointerGetBlockNumber(iptr);
	val <<= MaxHeapTuplesPerPageBits;
	val |= GinItemPointerGetOffsetNumber(iptr);

	return val;
}
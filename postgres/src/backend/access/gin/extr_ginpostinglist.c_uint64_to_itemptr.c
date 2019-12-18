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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinItemPointerSetBlockNumber (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GinItemPointerSetOffsetNumber (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ ) ; 
 int MaxHeapTuplesPerPageBits ; 

__attribute__((used)) static inline void
uint64_to_itemptr(uint64 val, ItemPointer iptr)
{
	GinItemPointerSetOffsetNumber(iptr, val & ((1 << MaxHeapTuplesPerPageBits) - 1));
	val = val >> MaxHeapTuplesPerPageBits;
	GinItemPointerSetBlockNumber(iptr, val);

	Assert(ItemPointerIsValid(iptr));
}
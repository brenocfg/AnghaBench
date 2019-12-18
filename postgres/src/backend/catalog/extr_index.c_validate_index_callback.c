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
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_2__ {int itups; int /*<<< orphan*/  tuplesort; } ;
typedef  TYPE_1__ ValidateIndexState ;
typedef  int /*<<< orphan*/  ItemPointer ;

/* Variables and functions */
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  itemptr_encode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplesort_putdatum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
validate_index_callback(ItemPointer itemptr, void *opaque)
{
	ValidateIndexState *state = (ValidateIndexState *) opaque;
	int64		encoded = itemptr_encode(itemptr);

	tuplesort_putdatum(state->tuplesort, Int64GetDatum(encoded), false);
	state->itups += 1;
	return false;				/* never actually delete anything */
}
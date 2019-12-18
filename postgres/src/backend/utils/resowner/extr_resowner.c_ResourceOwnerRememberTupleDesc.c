#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int /*<<< orphan*/  tupdescarr; } ;
typedef  TYPE_1__* ResourceOwner ;

/* Variables and functions */
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceArrayAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ResourceOwnerRememberTupleDesc(ResourceOwner owner, TupleDesc tupdesc)
{
	ResourceArrayAdd(&(owner->tupdescarr), PointerGetDatum(tupdesc));
}
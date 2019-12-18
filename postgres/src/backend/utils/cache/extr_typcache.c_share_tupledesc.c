#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  dsa_pointer ;
typedef  int /*<<< orphan*/  dsa_area ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_6__ {int /*<<< orphan*/  tdtypmod; } ;

/* Variables and functions */
 int /*<<< orphan*/  TupleDescCopy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TupleDescSize (TYPE_1__*) ; 
 int /*<<< orphan*/  dsa_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dsa_pointer
share_tupledesc(dsa_area *area, TupleDesc tupdesc, uint32 typmod)
{
	dsa_pointer shared_dp;
	TupleDesc	shared;

	shared_dp = dsa_allocate(area, TupleDescSize(tupdesc));
	shared = (TupleDesc) dsa_get_address(area, shared_dp);
	TupleDescCopy(shared, tupdesc);
	shared->tdtypmod = typmod;

	return shared_dp;
}
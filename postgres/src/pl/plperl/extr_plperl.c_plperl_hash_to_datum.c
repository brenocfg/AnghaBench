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
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HV ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ SvRV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plperl_build_tuple_result (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
plperl_hash_to_datum(SV *src, TupleDesc td)
{
	HeapTuple	tup = plperl_build_tuple_result((HV *) SvRV(src), td);

	return HeapTupleGetDatum(tup);
}
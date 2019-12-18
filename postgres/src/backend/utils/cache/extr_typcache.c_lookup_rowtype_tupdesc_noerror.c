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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/ * TupleDesc ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  PinTupleDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_rowtype_tupdesc_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

TupleDesc
lookup_rowtype_tupdesc_noerror(Oid type_id, int32 typmod, bool noError)
{
	TupleDesc	tupDesc;

	tupDesc = lookup_rowtype_tupdesc_internal(type_id, typmod, noError);
	if (tupDesc != NULL)
		PinTupleDesc(tupDesc);
	return tupDesc;
}
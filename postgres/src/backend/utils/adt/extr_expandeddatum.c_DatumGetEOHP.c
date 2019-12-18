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
typedef  int /*<<< orphan*/  varattrib_1b_e ;
struct TYPE_3__ {int /*<<< orphan*/ * eohptr; } ;
typedef  TYPE_1__ varatt_expanded ;
typedef  int /*<<< orphan*/  ptr ;
typedef  int /*<<< orphan*/  ExpandedObjectHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARATT_IS_EXPANDED_HEADER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARATT_IS_EXTERNAL_EXPANDED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARDATA_EXTERNAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

ExpandedObjectHeader *
DatumGetEOHP(Datum d)
{
	varattrib_1b_e *datum = (varattrib_1b_e *) DatumGetPointer(d);
	varatt_expanded ptr;

	Assert(VARATT_IS_EXTERNAL_EXPANDED(datum));
	memcpy(&ptr, VARDATA_EXTERNAL(datum), sizeof(ptr));
	Assert(VARATT_IS_EXPANDED_HEADER(ptr.eohptr));
	return ptr.eohptr;
}
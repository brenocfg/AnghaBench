#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {int /*<<< orphan*/  atttypid; } ;
struct TYPE_7__ {int /*<<< orphan*/  atttypid; } ;
struct TYPE_6__ {int natts; } ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int FirstLowInvalidHeapAttributeNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ SPI_ERROR_NOATTRIBUTE ; 
 scalar_t__ SPI_result ; 
 TYPE_4__* SystemAttributeDefinition (int) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 

Oid
SPI_gettypeid(TupleDesc tupdesc, int fnumber)
{
	SPI_result = 0;

	if (fnumber > tupdesc->natts || fnumber == 0 ||
		fnumber <= FirstLowInvalidHeapAttributeNumber)
	{
		SPI_result = SPI_ERROR_NOATTRIBUTE;
		return InvalidOid;
	}

	if (fnumber > 0)
		return TupleDescAttr(tupdesc, fnumber - 1)->atttypid;
	else
		return (SystemAttributeDefinition(fnumber))->atttypid;
}
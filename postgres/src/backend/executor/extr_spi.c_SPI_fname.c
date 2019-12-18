#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {int /*<<< orphan*/  attname; } ;
struct TYPE_7__ {int natts; } ;
typedef  TYPE_2__ FormData_pg_attribute ;

/* Variables and functions */
 int FirstLowInvalidHeapAttributeNumber ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ SPI_ERROR_NOATTRIBUTE ; 
 scalar_t__ SPI_result ; 
 TYPE_2__* SystemAttributeDefinition (int) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

char *
SPI_fname(TupleDesc tupdesc, int fnumber)
{
	const FormData_pg_attribute *att;

	SPI_result = 0;

	if (fnumber > tupdesc->natts || fnumber == 0 ||
		fnumber <= FirstLowInvalidHeapAttributeNumber)
	{
		SPI_result = SPI_ERROR_NOATTRIBUTE;
		return NULL;
	}

	if (fnumber > 0)
		att = TupleDescAttr(tupdesc, fnumber - 1);
	else
		att = SystemAttributeDefinition(fnumber);

	return pstrdup(NameStr(att->attname));
}